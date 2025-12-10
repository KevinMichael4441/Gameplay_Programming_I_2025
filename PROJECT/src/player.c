#include "./gameobjects/player.h"

/**
 * InitPlayer - Spins up a fresh Player.
 *
 * Grabs memory, loads the sprite sheet, sets up the collider and FSM,
 * and drops the poor eejit in the middle of the screen with full health,
 * full stamina, and not a clue what's coming.
 */

Player *InitPlayer(const char *name, Vector2 position, int radius)
{
	// Allocate memory for the Player structure
	Player *player = (Player *)malloc(sizeof(Player));

	// Check if memory allocation failed
	if (!player)
	{
		// Print an error message to stderr and terminate the program if allocation fails
		fprintf(stderr, "Failed to allocate player\n");
		exit(1);
	}

	// Load player texture
	Texture2D defaultTexture = LoadTexture("./assets/player_sprite_sheet.png");
	player->bufferTexture = defaultTexture;

	Image speedBuffPlayerImage = LoadImageFromTexture(defaultTexture);
	ImageColorTint(&speedBuffPlayerImage, GREEN);
	player->speedTexture = LoadTextureFromImage(speedBuffPlayerImage);
	UnloadImage(speedBuffPlayerImage);

	Image regenBuffPlayerImage = LoadImageFromTexture(defaultTexture);
	ImageColorTint(&regenBuffPlayerImage, PURPLE);
	player->regenTexture = LoadTextureFromImage(regenBuffPlayerImage);
	UnloadImage(regenBuffPlayerImage);

	// Setup Collide
	c2Circle collider = (c2Circle){.p = {position.x, position.y}, .r = radius};

	InitGameObject(&player->base,
				   name,	   // Name
				   position,   // Position
				   STATE_IDLE, // Initial State
				   DARKGREEN,  // Player Color
				   collider,   // cute_c2 Circle Collider
				   defaultTexture,	   // Player spritesheet
				   100,		   // Initial Health
				   2			// Lives
	);

	player->mana = 100;

	player->hasRegenBuff = false;
	player->hasSpeedBuff = false;
	player->buffTimer = 0;

	// Init the Player FSM
	InitPlayerFSM(&player->base);

	if (player->base.currentState == STATE_IDLE)
	{
		// Initialize the idle animation immediately
		PlayerEnterIdle(&player->base, 0.0f); // Trigger idle animation at initialization
	}

	return player;
}

/**
 * DeletePlayer - Clears out a Player and its base GameObject.
 *
 * If the Player ever owned anything fancy (swords, shields, emotional baggage),
 * this would be the place to free it. For now we just hand it off to DeleteGameObject.
 */

void DeletePlayer(GameObject *object)
{
	// Perform any player-specific cleanup here
	// Cast to Player if player-specific cleanup is required
	Player *player = (Player *)object;
	// Example of potential cleanup (not implemented here):
	// If the player is holding a dynamically allocated object, such as a Shield:
	// free(player->holding);
	// Perform any player-specific cleanup here
	UnloadTexture(player->bufferTexture);
	UnloadTexture(player->regenTexture);
	UnloadTexture(player->speedTexture);
	DeleteGameObject(object);
}

/**
 * InitPlayerFSM - Sets up all the Player states and their rules.
 *
 * Wires up which states can follow which, and which functions get called
 * when we enter, update or exit them. It's the bouncer at the door saying
 * "you're not going from Dead to Walking, pal". Go clean yourself off, dust
 * yourself down and respawn there like a good lad.
 */

void InitPlayerFSM(GameObject *object)
{
	object->stateConfigs = (StateConfig *)malloc(sizeof(StateConfig) * STATE_COUNT);
	if (!object->stateConfigs)
	{
		fprintf(stderr, "Failed to allocate state configs\n");
		exit(1);
	}

	// ---- STATE_IDLE state configuration ----
	// Define valid transitions from STATE_IDLE
	EventStateTransition idleValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_MOVE, STATE_WALKING},
		{EVENT_ATTACK, STATE_ATTACKING},
		{EVENT_DEFEND, STATE_SHIELD},
		{EVENT_DIE, STATE_DEAD},
		{EVENT_SPECIAL, STATE_SPECIAL}};
	// Set up the state configuration for STATE_IDLE
	InitStateConfig(object, STATE_IDLE, "Player_Idle", PlayerEnterIdle, PlayerUpdateIdle, PlayerExitIdle);
	// Configure valid transitions for STATE_IDLE
	StateTransitions(&object->stateConfigs[STATE_IDLE], idleValidTransitions, sizeof(idleValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_WALKING state configuration ----
	// Define valid transitions from STATE_WALKING
	EventStateTransition walkingValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_NONE, STATE_IDLE},
		{EVENT_ATTACK, STATE_ATTACKING},
		{EVENT_DIE, STATE_DEAD},
		{EVENT_SPECIAL, STATE_SPECIAL}};
	// Set up the state configuration for STATE_WALKING
	InitStateConfig(object, STATE_WALKING, "Player_Walking", PlayerEnterWalking, PlayerUpdateWalking, PlayerExitWalking);
	// Configure valid transitions for STATE_WALKING
	StateTransitions(&object->stateConfigs[STATE_WALKING], walkingValidTransitions, sizeof(walkingValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_SPECIAL state configuration ----
	// Define valid transitions from STATE_WALKING
	EventStateTransition specialValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_NONE, STATE_IDLE}};
	// Set up the state configuration for STATE_WALKING
	InitStateConfig(object, STATE_SPECIAL, "Player_Buffing", PlayerEnterSpecial, PlayerUpdateSpecial, PlayerExitSpecial);
	// Configure valid transitions for STATE_WALKING
	StateTransitions(&object->stateConfigs[STATE_SPECIAL], specialValidTransitions, sizeof(specialValidTransitions) / sizeof(EventStateTransition));


	// ---- STATE_ATTACKING state configuration ----
	// Define valid transitions from STATE_ATTACKING
	EventStateTransition attackValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_NONE, STATE_IDLE},
		{EVENT_MOVE, STATE_WALKING},
		{EVENT_DEFEND, STATE_SHIELD},
		{EVENT_DIE, STATE_DEAD}};
	// Set up the state configuration for STATE_ATTACKING
	InitStateConfig(object, STATE_ATTACKING, "Player_Attacking", PlayerEnterAttacking, PlayerUpdateAttacking, PlayerExitAttacking);
	// Configure valid transitions for STATE_ATTACKING
	StateTransitions(&object->stateConfigs[STATE_ATTACKING], attackValidTransitions, sizeof(attackValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_SHIELD state configuration ----
	// Define valid transitions from STATE_SHIELD
	EventStateTransition sheildingValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_NONE, STATE_IDLE},
		{EVENT_MOVE, STATE_WALKING},
		{EVENT_ATTACK, STATE_ATTACKING},
		{EVENT_DIE, STATE_DEAD}};
	// Set up the state configuration for STATE_SHIELD
	InitStateConfig(object, STATE_SHIELD, "Player_Shielding", PlayerEnterShielding, PlayerUpdateShielding, PlayerExitShielding);
	// Configure valid transitions for STATE_SHIELD
	StateTransitions(&object->stateConfigs[STATE_SHIELD], sheildingValidTransitions, sizeof(sheildingValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_DEAD state configuration ----
	// Define valid transitions from STATE_DEAD
	EventStateTransition deadValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_RESPAWN, STATE_RESPAWN}};
	// Set up the state configuration for STATE_DEAD
	InitStateConfig(object, STATE_DEAD, "Player_Dead", PlayerEnterDie, PlayerUpdateDie, PlayerExitDie);
	// Configure valid transitions for STATE_DEAD
	StateTransitions(&object->stateConfigs[STATE_DEAD], deadValidTransitions, sizeof(deadValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_RESPAWN state configuration ----
	// Define valid transitions from STATE_RESPAWN
	EventStateTransition respawnValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_RESPAWN, STATE_IDLE}};
	// Set up the state configuration for STATE_RESPAWN
	InitStateConfig(object, STATE_RESPAWN, "Player_Respawn", PlayerEnterRespawn, PlayerUpdateRespawn, PlayerExitRespawn);
	// Configure valid transitions for STATE_RESPAWN
	StateTransitions(&object->stateConfigs[STATE_RESPAWN], respawnValidTransitions, sizeof(respawnValidTransitions) / sizeof(EventStateTransition));

	// Empty config for unimplemented STATE
	// STATE_COLLISION
	object->stateConfigs[STATE_COLLISION] = UNIMPLEMENTED_STATE_CONFIG;

	// Print out Configs
	PrintStateConfigs(object->stateConfigs, STATE_COUNT);
}

/**
 * PlayerMove - Shuffles the Player along the input axis.
 *
 * Updates both position and collider so collisions don't think
 * we're still back where we started three seconds ago.
 */

void PlayerMove(Player *player, Vector2 inputAxis, float deltaTime)
{
	float speed; 
	
	if (player->hasSpeedBuff)
	{
		speed = 200.0f;
	}
	else
	{
		speed = 130.0f;
	}

	player->base.position.x += inputAxis.x * speed * deltaTime;
	player->base.position.y += inputAxis.y * speed * deltaTime;

	// Hold on screen
	ClampGameObjectOnScreen(&player->base);

	// Update Collider
	player->base.collider.p.x = player->base.position.x;
	player->base.collider.p.y = player->base.position.y;
}

/**
 * SelectRandomIdleAnimation - Picks a random idle from the sheet.
 *
 * Just to keep the lad from looking like a statue. Chooses one of several
 * rows and wires it into the animation system.
 */

void PlayerRandomIdleAnimation(GameObject *object, float deltaTime)
{
	(void)deltaTime;

	// See grid_player_sprite_sheet.png for rows and columns
	int randomChoice = rand() % 7 + 1;

	Rectangle idle1[8] = {
		{0, 320, 64, 64},	// Frame 1: Row 6, Column 1
		{64, 320, 64, 64},	// Frame 2: Row 6, Column 2
		{128, 320, 64, 64}, // Frame 3: Row 6, Column 3
		{192, 320, 64, 64}, // Frame 4: Row 6, Column 4
		{256, 320, 64, 64}, // Frame 5: Row 6, Column 5
		{320, 320, 64, 64}, // Frame 6: Row 6, Column 6
		{384, 320, 64, 64}, // Frame 7: Row 6, Column 7
		{448, 320, 64, 64}	// Frame 8: Row 6, Column 8
	};

	Rectangle idle2[8] = {
		{0, 384, 64, 64},	// Frame 1: Row 7, Column 1
		{64, 384, 64, 64},	// Frame 2: Row 7, Column 2
		{128, 384, 64, 64}, // Frame 3: Row 7, Column 3
		{192, 384, 64, 64}, // Frame 4: Row 7, Column 4
		{256, 384, 64, 64}, // Frame 5: Row 7, Column 5
		{320, 384, 64, 64}, // Frame 6: Row 7, Column 6
		{384, 384, 64, 64}, // Frame 7: Row 7, Column 7
		{448, 384, 64, 64}	// Frame 8: Row 7, Column 8
	};

	Rectangle idle3[8] = {
		{0, 448, 64, 64},	// Frame 1: Row 8, Column 1
		{64, 448, 64, 64},	// Frame 2: Row 8, Column 2
		{128, 448, 64, 64}, // Frame 3: Row 8, Column 3
		{192, 448, 64, 64}, // Frame 4: Row 8, Column 4
		{256, 448, 64, 64}, // Frame 5: Row 8, Column 5
		{320, 448, 64, 64}, // Frame 6: Row 8, Column 6
		{384, 448, 64, 64}, // Frame 7: Row 8, Column 7
		{448, 448, 64, 64}	// Frame 8: Row 8, Column 8
	};

	Rectangle idle4[7] = {
		{0, 0, 64, 64},	 	// Frame 1: Row 1, Column 1
		{64, 0, 64, 64},	// Frame 2: Row 1, Column 2
		{128, 0, 64, 64}, 	// Frame 3: Row 1, Column 3
		{192, 0, 64, 64},	// Frame 4: Row 1, Column 4
		{256, 0, 64, 64}, 	// Frame 5: Row 1, Column 5
		{320, 0, 64, 64}, 	// Frame 6: Row 1, Column 6
		{384, 0, 64, 64}, 	// Frame 7: Row 1, Column 7
	};

	Rectangle idle5[7] = {
		{0, 64, 64, 64},	// Frame 1: Row 2, Column 1
		{64, 64, 64, 64},	// Frame 2: Row 2, Column 2
		{128, 64, 64, 64}, 	// Frame 3: Row 2, Column 3
		{192, 64, 64, 64}, 	// Frame 4: Row 2, Column 4
		{256, 64, 64, 64}, 	// Frame 5: Row 2, Column 5
		{320, 64, 64, 64}, 	// Frame 6: Row 2, Column 6
		{384, 64, 64, 64}, 	// Frame 7: Row 2, Column 7
	};

	Rectangle idle6[7] = {
		{0, 128, 64, 64},	 // Frame 1: Row 3, Column 1
		{64, 128, 64, 64},	 // Frame 2: Row 3, Column 2
		{128, 128, 64, 64}, // Frame 3: Row 3, Column 3
		{192, 128, 64, 64}, // Frame 4: Row 3, Column 4
		{256, 128, 64, 64}, // Frame 5: Row 3, Column 5
		{320, 128, 64, 64}, // Frame 6: Row 3, Column 6
		{384, 128, 64, 64}, // Frame 7: Row 3, Column 7
	};

	Rectangle idle7[7] = {
		{0, 192, 64, 64},	 // Frame 1: Row 4, Column 1
		{64, 192, 64, 64},	 // Frame 2: Row 4, Column 2
		{128, 192, 64, 64}, // Frame 3: Row 4, Column 3
		{192, 192, 64, 64}, // Frame 4: Row 4, Column 4
		{256, 192, 64, 64}, // Frame 5: Row 4, Column 5
		{320, 192, 64, 64}, // Frame 6: Row 4, Column 6
		{384, 192, 64, 64}, // Frame 7: Row 4, Column 7
	};

	switch (randomChoice)
	{
	case 1:
		InitGameObjectAnimation(object, idle1, 8, 0.18f); // Animation 1
		break;
	case 2:
		InitGameObjectAnimation(object, idle2, 8, 0.18f); // Animation 2
		break;
	case 3:
		InitGameObjectAnimation(object, idle3, 8, 0.18f); // Animation 3
		break;
	case 4:
		InitGameObjectAnimation(object, idle4, 8, 0.18f); // Animation 3
		break;
	case 5:
		InitGameObjectAnimation(object, idle5, 8, 0.18f); // Animation 3
		break;
	case 6:
		InitGameObjectAnimation(object, idle6, 8, 0.18f); // Animation 3
		break;
	case 7:
		InitGameObjectAnimation(object, idle7, 8, 0.18f); // Animation 3
		break;
	default:
		InitGameObjectAnimation(object, idle1, 8, 0.18f); // Default to Animation 1
		break;
	}
}

void PlayerEnterIdle(GameObject *object, float deltaTime)
{
	Player *player = (Player *)object;
	printf("\n%s -> ENTER -> Idle\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);

	if (player->base.previousState != player->base.currentState && player->base.currentState == STATE_IDLE)
	{
		PlayerRandomIdleAnimation(&player->base, deltaTime);
	}
	object->timer = 0.0f;
}

void PlayerUpdateIdle(GameObject *object, float deltaTime)
{
	Player *player = (Player *)object;
	printf("\n%s -> UPDATE -> Idle\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	//  Complete the remainder of the method
	UpdateAnimation(&object->animation, deltaTime);

	// Check if the animation has finished
	if (object->animation.currentFrame == object->animation.frameCount - 1)
	{
		// Transition to a another idle animation
		PlayerRandomIdleAnimation(object, deltaTime); // Trigger idle animation
	}

	AllStatePlayerUpdate(object, deltaTime);
}

void PlayerExitIdle(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	Player *player = (Player *)object;
	(void)player;
	printf("\n%s <- EXIT <- Idle\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method
	object->timer = 0.0f;
}

/**
 * InitWalkAnimation - Picks the right walk row based on direction.
 *
 * Uses currentDirection on the GameObject and points the animation
 * at the matching sprites in the sheet.
 */

static void InitWalkAnimation(Player *player)
{
	// WALK UP (Row 9)
	static Rectangle walk_UP[9] = {
		{0, 512, 64, 64},	// Frame 1: Row 9, Column 1
		{64, 512, 64, 64},	// Frame 2: Row 9, Column 2
		{128, 512, 64, 64}, // Frame 3: Row 9, Column 3
		{192, 512, 64, 64}, // Frame 4: Row 9, Column 4
		{256, 512, 64, 64}, // Frame 5: Row 9, Column 5
		{320, 512, 64, 64}, // Frame 6: Row 9, Column 6
		{384, 512, 64, 64}, // Frame 7: Row 9, Column 7
		{448, 512, 64, 64}, // Frame 8: Row 9, Column 8
		{512, 512, 64, 64}	// Frame 9: Row 9, Column 9
	};

	// WALK DOWN (Row 10)
	static Rectangle walk_DOWN[9] = {
		{0, 640, 64, 64},	// Frame 1: Row 10, Column 1
		{64, 640, 64, 64},	// Frame 2: Row 10, Column 2
		{128, 640, 64, 64}, // Frame 3: Row 10, Column 3
		{192, 640, 64, 64}, // Frame 4: Row 10, Column 4
		{256, 640, 64, 64}, // Frame 5: Row 10, Column 5
		{320, 640, 64, 64}, // Frame 6: Row 10, Column 6
		{384, 640, 64, 64}, // Frame 7: Row 10, Column 7
		{448, 640, 64, 64}, // Frame 8: Row 10, Column 8
		{512, 640, 64, 64}	// Frame 9: Row 10, Column 9
	};

	// WALK LEFT (Row 11)
	static Rectangle walk_LEFT[9] = {
		{0, 576, 64, 64},	// Frame 1: Row 11, Column 1
		{64, 576, 64, 64},	// Frame 2: Row 11, Column 2
		{128, 576, 64, 64}, // Frame 3: Row 11, Column 3
		{192, 576, 64, 64}, // Frame 4: Row 11, Column 4
		{256, 576, 64, 64}, // Frame 5: Row 11, Column 5
		{320, 576, 64, 64}, // Frame 6: Row 11, Column 6
		{384, 576, 64, 64}, // Frame 7: Row 11, Column 7
		{448, 576, 64, 64}, // Frame 8: Row 11, Column 8
		{512, 576, 64, 64}	// Frame 9: Row 11, Column 9
	};

	// WALK RIGHT (Row 12)
	static Rectangle walk_RIGHT[9] = {
		{0, 704, 64, 64},	// Frame 1: Row 12, Column 1
		{64, 704, 64, 64},	// Frame 2: Row 12, Column 2
		{128, 704, 64, 64}, // Frame 3: Row 12, Column 3
		{192, 704, 64, 64}, // Frame 4: Row 12, Column 4
		{256, 704, 64, 64}, // Frame 5: Row 12, Column 5
		{320, 704, 64, 64}, // Frame 6: Row 12, Column 6
		{384, 704, 64, 64}, // Frame 7: Row 12, Column 7
		{448, 704, 64, 64}, // Frame 8: Row 12, Column 8
		{512, 704, 64, 64}	// Frame 9: Row 12, Column 9
	};

	GameObject *object = &player->base;

	switch (object->currentDirection)
	{
	case UP:
		InitGameObjectAnimation(object, walk_UP, 9, 0.055f);
		break;
	case DOWN:
		InitGameObjectAnimation(object, walk_DOWN, 9, 0.055f);
		break;
	case LEFT:
		InitGameObjectAnimation(object, walk_LEFT, 9, 0.055f);
		break;
	case RIGHT:
		InitGameObjectAnimation(object, walk_RIGHT, 9, 0.055f);
		break;
	}
}

void PlayerEnterWalking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	Player *player = (Player *)object;
	printf("\n%s -> ENTER -> Walking\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method
	InitWalkAnimation(player);
	object->timer = 0.0f;
}

void PlayerUpdateWalking(GameObject *object, float deltaTime)
{
	Player *player = (Player *)object;
	printf("\n%s -> UPDATE -> Walking\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method

	// Move according to inputAxis
	PlayerMove(player, object->inputAxis, deltaTime);

	// Check if moving and direction changed since last frame
	if (Vector2Length(object->inputAxis) > 0.0f &&
		object->currentDirection != object->previousDirection)
	{
		InitWalkAnimation(player);
		object->previousDirection = object->currentDirection;
	}

	// Update the Animation
	UpdateAnimation(&object->animation, deltaTime);


	AllStatePlayerUpdate(object, deltaTime);
}

void PlayerExitWalking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	Player *player = (Player *)object;
	printf("\n%s <- EXIT <- Walking\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method
	object->timer = 0.0f;
}


void PlayerEnterSpecial(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	Player *player = (Player *)object;
	printf("\n%s -> ENTER -> Special\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);

	if (player->mana > 50 && !player->hasRegenBuff && !player->hasSpeedBuff)
	{
		player->mana -= 50;

		int buff = rand() % 2;
		if (buff == 0)
		{
			player->hasSpeedBuff = true;
			player->base.keyframes = player->speedTexture;
		}
		else
		{
			player->hasRegenBuff = true;
			player->base.keyframes = player->regenTexture;
		}
	}

	object->timer = 0.0f;
}

void PlayerUpdateSpecial(GameObject *object, float deltaTime)
{
	(void)object;
	(void)deltaTime;
	ChangeState(object, STATE_IDLE, deltaTime);
}

void PlayerExitSpecial(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	Player *player = (Player *)object;
	//printf("\n%s <- EXIT <- Special\n", object->name);
	//printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method
	object->timer = 0.0f;
	player->buffTimer = 0.0f;
}

/**
 * InitAttackAnimation - Picks the correct attack arc for the direction.
 *
 * Uses the big 192x192 attack frames further down the sprite sheet.
 */

static void InitAttackAnimation(Player *player)
{
	// ATTACK UP (Row 48)
	static Rectangle sword_attack_UP[6] = {
		{0, 2952, 192, 192},   // Frame 1: Row 44, Column 1
		{192, 2952, 192, 192}, // Frame 2: Row 44, Column 2
		{384, 2952, 192, 192}, // Frame 3: Row 44, Column 3
		{576, 2952, 192, 192}, // Frame 4: Row 44, Column 4
		{768, 2952, 192, 192}, // Frame 5: Row 44, Column 5
		{960, 2952, 192, 192}  // Frame 6: Row 44, Column 6
	};

	// ATTACK LEFT (Row 51)
	static Rectangle sword_attack_LEFT[6] = {
		{0, 3144, 192, 192},   // Frame 1: Row 51, Column 1
		{192, 3144, 192, 192}, // Frame 2: Row 51, Column 2
		{384, 3144, 192, 192}, // Frame 3: Row 51, Column 3
		{576, 3144, 192, 192}, // Frame 4: Row 51, Column 4
		{768, 3144, 192, 192}, // Frame 5: Row 51, Column 5
		{960, 3144, 192, 192}  // Frame 6: Row 51, Column 6
	};

	// ATTACK DOWN (Row 54)
	static Rectangle sword_attack_DOWN[6] = {
		{0, 3336, 192, 192},   // Frame 1: Row 54, Column 1
		{192, 3336, 192, 192}, // Frame 2: Row 54, Column 2
		{384, 3336, 192, 192}, // Frame 3: Row 54, Column 3
		{576, 3336, 192, 192}, // Frame 4: Row 54, Column 4
		{768, 3336, 192, 192}, // Frame 5: Row 54, Column 5
		{960, 3336, 192, 192}  // Frame 6: Row 54, Column 6
	};

	// ATTACK RIGHT (Row 57)
	static Rectangle sword_attack_RIGHT[6] = {
		{0, 3528, 192, 192},   // Frame 1: Row 57, Column 1
		{192, 3528, 192, 192}, // Frame 2: Row 57, Column 2
		{384, 3528, 192, 192}, // Frame 3: Row 57, Column 3
		{576, 3528, 192, 192}, // Frame 4: Row 57, Column 4
		{768, 3528, 192, 192}, // Frame 5: Row 57, Column 5
		{960, 3528, 192, 192}  // Frame 6: Row 57, Column 6
	};

	GameObject *object = &player->base;

	switch (object->currentDirection)
	{
	case UP:
		InitGameObjectAnimation(object, sword_attack_UP, 6, 0.035f);
		break;
	case DOWN:
		InitGameObjectAnimation(object, sword_attack_DOWN, 6, 0.035f);
		break;
	case LEFT:
		InitGameObjectAnimation(object, sword_attack_LEFT, 6, 0.035f);
		break;
	case RIGHT:
		InitGameObjectAnimation(object, sword_attack_RIGHT, 6, 0.035f);
		break;
	}
}

void PlayerEnterAttacking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	Player *player = (Player *)object;
	printf("\n%s -> ENTER -> Attacking\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method
	// Example: Deduct some stamina when attacking
	InitAttackAnimation(player);

	player->mana -= 10 ;
	if (player->mana <= 0)
	{
		ChangeState(object, STATE_IDLE, deltaTime);
	}
	player->mana = Clamp(player->mana,0,100);

	object->timer = 0.0f;

	object->timer = 0;
}

void PlayerUpdateAttacking(GameObject *object, float deltaTime)
{
	Player *player = (Player *)object;
	printf("\n%s -> UPDATE -> Attacking\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method
	// Check if the attack should end or be interrupted (e.g., stamina depletion)

	// Move according to inputAxis
	PlayerMove(player, object->inputAxis, deltaTime);

	// Check if moving and direction changed since last frame
	if (Vector2Length(object->inputAxis) != 0.0f &&
		object->currentDirection != object->previousDirection)
	{
		InitAttackAnimation(player);
		object->previousDirection = object->currentDirection;
	}

	// Update the Animation
	UpdateAnimation(&object->animation, deltaTime);


	AllStatePlayerUpdate(object, deltaTime);

}

void PlayerExitAttacking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	Player *player = (Player *)object;
	printf("\n%s <- EXIT <- Attacking\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method
	// Reset or adjust any temporary changes during attack, if needed

	object->timer = 0.0f;
}

static void InitShieldAnimation(Player *player)
{
	// ATTACK UP (Row 48)
	static Rectangle shield_UP[8] = {
		{0, 256, 64, 64},   // Frame 1: Row 5, Column 1
		{64, 256, 64, 64}, // Frame 2: Row 5, Column 2
		{128, 256, 64, 64}, // Frame 3: Row 5, Column 3
		{192, 256, 64, 64}, // Frame 4: Row 5, Column 4
		{256, 256, 64, 64}, // Frame 5: Row 5, Column 5
		{320, 256, 64, 64},  // Frame 6: Row 5, Column 6
		{384, 256, 64, 64}, // Frame 7: Row 5, Column 7
		{448, 256, 64, 64}  // Frame 8: Row 5, Column 8
	};

	// ATTACK LEFT (Row 51)
	static Rectangle shield_LEFT[8] = {
		{0, 320, 64, 64},   // Frame 1: Row 5, Column 1
		{64, 320, 64, 64}, // Frame 2: Row 5, Column 2
		{128, 320, 64, 64}, // Frame 3: Row 5, Column 3
		{192, 320, 64, 64}, // Frame 4: Row 5, Column 4
		{256, 320, 64, 64}, // Frame 5: Row 5, Column 5
		{320, 320, 64, 64},  // Frame 6: Row 5, Column 6
		{384, 320, 64, 64}, // Frame 7: Row 5, Column 7
		{448, 320, 64, 64}  // Frame 8: Row 5, Column 8
	};



	// ATTACK DOWN (Row 54)
	static Rectangle shield_DOWN[8] = {
		{0, 384, 64, 64},   // Frame 1: Row 5, Column 1
		{64, 384, 64, 64}, // Frame 2: Row 5, Column 2
		{128, 384, 64, 64}, // Frame 3: Row 5, Column 3
		{192, 384, 64, 64}, // Frame 4: Row 5, Column 4
		{256, 384, 64, 64}, // Frame 5: Row 5, Column 5
		{320, 384, 64, 64},  // Frame 6: Row 5, Column 6
		{384, 384, 64, 64}, // Frame 7: Row 5, Column 7
		{448, 384, 64, 64}  // Frame 8: Row 5, Column 8
	};


	// ATTACK RIGHT (Row 57)
	static Rectangle SHIELD_RIGHT[8] = {
		{0, 448, 64, 64},   // Frame 1: Row 5, Column 1
		{64, 448, 64, 64}, // Frame 2: Row 5, Column 2
		{128, 448, 64, 64}, // Frame 3: Row 5, Column 3
		{192, 448, 64, 64}, // Frame 4: Row 5, Column 4
		{256, 448, 64, 64}, // Frame 5: Row 5, Column 5
		{320, 448, 64, 64},  // Frame 6: Row 5, Column 6
		{384, 448, 64, 64}, // Frame 7: Row 5, Column 7
		{448, 448, 64, 64}  // Frame 8: Row 5, Column 8
	};


	GameObject *object = &player->base;

	switch (object->currentDirection)
	{
	case UP:
		InitGameObjectAnimation(object, shield_UP, 8, 0.035f);
		break;
	case DOWN:
		InitGameObjectAnimation(object, shield_DOWN, 8, 0.035f);
		break;
	case LEFT:
		InitGameObjectAnimation(object, shield_LEFT, 8, 0.035f);
		break;
	case RIGHT:
		InitGameObjectAnimation(object, SHIELD_RIGHT, 8, 0.035f);
		break;
	}
}


void PlayerEnterShielding(GameObject *object, float deltaTime)
{
	// TODO : Not Currently Implemented
	(void)deltaTime;
	Player *player = (Player *)object;
	printf("\n%s -> ENTER -> Sheilding\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);


	InitShieldAnimation(player);

	player->mana -= 10 ;
	if (player->mana <= 0)
	{
		ChangeState(object, STATE_IDLE, deltaTime);
	}
	player->mana = Clamp(player->mana,0,100);

	object->timer = 0.0f;
}
void PlayerUpdateShielding(GameObject *object, float deltaTime)
{
	Player *player = (Player *)object;
	printf("\n%s -> UPDATE -> Sheilding\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method
	// Example: Check if the shielding duration is over or if stamina is depleted
	UpdateAnimation(&object->animation, deltaTime);

	AllStatePlayerUpdate(object, deltaTime);
}

void PlayerExitShielding(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	Player *player = (Player *)object;
	printf("\n%s <- EXIT <- Sheilding\n", object->name);
	printf("Lives: %d\n\n", player->base.lives);
	// Complete the remainder of the method
	// Reset any temporary shielding effects if necessary

	object->timer = 0.0f;
}

void PlayerEnterDie(GameObject *object, float deltaTime)
{
	// TODO : Not Currently Implemented
	(void)deltaTime;
	printf("\n%s -> ENTER -> Die\n", object->name);
	// Complete the remainder of the method

	object->timer = 0.0f;

		static Rectangle die[8] = {
		{0, 1280, 64, 64},	// Frame 1: Row 20, Column 1
		{64, 1280, 64, 64},	// Frame 2: Row 20, Column 2
		{128, 1280, 64, 64}, // Frame 3: Row 20, Column 3
		{192, 1280, 64, 64}, // Frame 4: Row 20, Column 4
		{256, 1280, 64, 64}, // Frame 5: Row 20, Column 5
		{320, 1280, 64, 64}, // Frame 6: Row 20, Column 6
		{320, 1280, 64, 64}, // Frame 7: Row 20, Column 6
		{320, 1280, 64, 64}, // Frame 8: Row 20, Column 6
	};

	InitGameObjectAnimation(object, die, 8, 0.25f);
}

void PlayerUpdateDie(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	printf("\n%s -> UPDATE -> Die\n", object->name);
	
	// Complete the remainder of the method
	UpdateAnimation(&object->animation, deltaTime);

	float duration = 2.0f;
	object->timer += deltaTime;

	if (object->timer >= duration)
	{
		ChangeState(object, STATE_RESPAWN, deltaTime);
	}

}

void PlayerExitDie(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	printf("\n%s <- EXIT <- Die\n", object->name);
	// Complete the remainder of the method

	object->timer = 0.0f;
	object->position.x = -1000.0f;
	object->position.y = -1000.0f;
	object->collider.p.x = object->position.x;
	object->collider.p.y = object->position.y;
}

void PlayerEnterRespawn(GameObject *object, float deltaTime)
{
	// TODO : Not Currently Implemented
	(void)deltaTime;
	printf("\n%s -> ENTER -> Respawn\n", object->name);
	// Complete the remainder of the method
	object->timer = 0.0f;
	object->lives--;
}

void PlayerUpdateRespawn(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	printf("\n%s -> UPDATE -> Respawn\n", object->name);
	// Complete the remainder of the method
	UpdateAnimation(&object->animation, deltaTime);

	float duration = 2.0f;
	object->timer += deltaTime;

	if (object->timer >= duration)
	{
		ChangeState(object, STATE_IDLE, deltaTime);
	}
}

void PlayerExitRespawn(GameObject *object, float deltaTime)
{
	Player *player = (Player *)object;
	(void)deltaTime;
	printf("\n%s <- EXIT <- Respawn\n", object->name);
	// Complete the remainder of the method

	object->timer = 0.0f;
	
	object->position.x = SCREEN_WIDTH/2;
	object->position.y = SCREEN_HEIGHT/2;
	object->collider.p.x = object->position.x;
	object->collider.p.y = object->position.y;
	
	object->health = 100.0f;
	player->mana = 100.0f;
	player->hasRegenBuff = false;
	player->hasSpeedBuff = false;
}

void AllStatePlayerUpdate(GameObject *object, float deltaTime)
{
	Player *player = (Player *)object;

	if (player->base.health <= 0)
	{
		ChangeState(object, STATE_DEAD, deltaTime);
	}

	object->timer += deltaTime;
	player->buffTimer += deltaTime;

	if (object->timer >= 0.5f)
	{
		player->mana += 8;
		player->mana = Clamp(player->mana, 0, 100);
		object->timer = 0.0f;

		if (player->hasRegenBuff)
		{
			player->base.health += 4;
			player->base.health = Clamp(player->base.health, 0, 100);
		}
	}

	if (player->buffTimer > 5.0f)
	{
		player->hasRegenBuff = false;
		player->hasSpeedBuff = false;
		player->buffTimer = 0.0f;
		object->keyframes = player->bufferTexture;
	}
}