#include "./gameobjects/npc.h"

/**
 * InitNPC - Sets up a brand-new NPC and gets them ready for mischief.
 *
 * @name:     The NPC's name ... purely for debugging and adds a bit of personality.
 * @position: Where the NPC spawns into the world.
 * @radius:   Collider radius (because even NPCs need personal space).
 *
 * Allocates the NPC, loads its sprite sheet, builds its collider,
 * sets aggression, health, and wires up the NPC-specific FSM.
 *
 * Returns: Pointer to the freshly-minted NPC.
 *          Exits the program if memory/texture loading fails.
 */

NPC *InitNPC(const char *name, Vector2 position, int radius)
{
	// Allocate memory for the NPC structure
	NPC *npc = (NPC *)malloc(sizeof(NPC));

	// Check if memory allocation failed
	if (!npc)
	{
		// Print an error message to stderr and terminate the program if allocation fails
		fprintf(stderr, "Failed to allocate NPC\n");
		exit(1);
	}

	// Load player texture
	Texture2D npcTexture = LoadTexture("./assets/npc_sprite_sheet.png");

	// Setup Collider
	c2Circle collider = (c2Circle){.p = {position.x, position.y}, .r = radius};

	// Initialize the base GameObject structure within the NPC with the provided name
	InitGameObject(&npc->base,
				   name,
				   position,   // Position
				   STATE_IDLE, // Initial State
				   DARKGREEN,  // Player Color
				   collider,   // cute_c2 Circle Collider
				   npcTexture,
				   200,	 // Initial Health
				   3	// Number of lives
	);

	// Set the default aggression level for the NPC
	npc->aggression = 50;

	// Initialize the NPC's finite state machine (FSM) with state configurations
	InitNPCFSM(&npc->base);

	if (npc->base.currentState == STATE_IDLE)
	{
		// Initialize the idle animation immediately
		NPCEnterIdle(&npc->base, 0.0f); // Trigger idle animation at initialization
	}

	// Return a pointer to the initialized NPC object
	return npc;
}

/**
 * DeleteNPC - Sends the NPC off to the big heap in the sky (Fly NPC Fly!).
 *
 * @object: The NPC's GameObject.
 *
 * Handles any NPC-specific teardown (none yet), then hands off to
 * DeleteGameObject for the real cleanup.
 */

void DeleteNPC(GameObject *object)
{
	// Perform any npc-specific cleanup here
	// Cast to NPC if npc-specific cleanup is required
	// NPC *npc = (NPC *)object;
	// Example of potential cleanup (not implemented here):
	// If the npc is holding a dynamically allocated object, such as a thor hammer:
	// free(npc->holding);
	DeleteGameObject(object);
}

/**
 * InitNPCFSM - Wires up the finite-state machine for an NPC.
 *
 * @object: The NPC's GameObject.
 *
 * Allocates the state configuration table, assigns handler
 * functions for each implemented state, and defines each state's
 * legal transitions. Unused states are filled with empty configs
 * so they don't cause chaos.
 */

void InitNPCFSM(GameObject *object)
{
	// Allocate memory for the state configurations array with a size for all possible states
	object->stateConfigs = (StateConfig *)malloc(sizeof(StateConfig) * STATE_COUNT);

	// Check if memory allocation for state configurations failed
	if (!object->stateConfigs)
	{
		// Print an error message and exit if allocation fails
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
		{EVENT_DIE, STATE_DEAD}};
	// Set up the state configuration for STATE_IDLE
	InitStateConfig(object, STATE_IDLE, "NPC_Idle", NPCEnterIdle, NPCUpdateIdle, NPCExitIdle);
	// Configure valid transitions for STATE_IDLE
	StateTransitions(&object->stateConfigs[STATE_IDLE], idleValidTransitions, sizeof(idleValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_WALKING state configuration ----
	// Define valid transitions from STATE_WALKING
	EventStateTransition walkingValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_NONE, STATE_IDLE},
		{EVENT_ATTACK, STATE_ATTACKING},
		{EVENT_DIE, STATE_DEAD}};
	// Set up the state configuration for STATE_WALKING
	InitStateConfig(object, STATE_WALKING, "NPC_Walking", NPCEnterWalking, NPCUpdateWalking, NPCExitWalking);
	// Configure valid transitions for STATE_WALKING
	StateTransitions(&object->stateConfigs[STATE_WALKING], walkingValidTransitions, sizeof(walkingValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_ATTACKING state configuration ----
	// Define valid transitions from STATE_ATTACKING
	EventStateTransition attackValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_NONE, STATE_IDLE},
		{EVENT_MOVE, STATE_WALKING},
		{EVENT_DIE, STATE_DEAD}};
	// Set up the state configuration for STATE_ATTACKING
	InitStateConfig(object, STATE_ATTACKING, "NPC_Attacking", NPCEnterAttacking, NPCUpdateAttacking, NPCExitAttacking);
	// Configure valid transitions for STATE_ATTACKING
	StateTransitions(&object->stateConfigs[STATE_ATTACKING], attackValidTransitions, sizeof(attackValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_SHIELD state configuration ----
	// Define valid transitions from STATE_SHIELD
	EventStateTransition sheildingValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_NONE, STATE_IDLE},
		{EVENT_ATTACK, STATE_ATTACKING},
		{EVENT_DIE, STATE_DEAD}};
	// Set up the state configuration for STATE_SHIELD
	InitStateConfig(object, STATE_SHIELD, "NPC_Shielding", NPCEnterShielding, NPCUpdateShielding, NPCExitShielding);
	// Configure valid transitions for STATE_SHIELD
	StateTransitions(&object->stateConfigs[STATE_SHIELD], sheildingValidTransitions, sizeof(sheildingValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_DEAD state configuration ----
	// Define valid transitions from STATE_DEAD
	EventStateTransition deadValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_RESPAWN, STATE_RESPAWN}}; // Should go to STATE_RESPAWN to keep kit small goes to IDLE
	// Set up the state configuration for STATE_DEAD
	InitStateConfig(object, STATE_DEAD, "NPC_Dead", NPCEnterDead, NPCUpdateDead, NPCExitDead);
	// Configure valid transitions for STATE_DEAD
	StateTransitions(&object->stateConfigs[STATE_DEAD], deadValidTransitions, sizeof(deadValidTransitions) / sizeof(EventStateTransition));

	// ---- STATE_RESPAWN state configuration ----
	// Define valid transitions from STATE_RESPAWN
	EventStateTransition respawnValidTransitions[] = {
		// EVENT -> STATE
		{EVENT_RESPAWN, STATE_IDLE}};
	// Set up the state configuration for STATE_RESPAWN
	InitStateConfig(object, STATE_RESPAWN, "NPC_Respawn", NPCEnterRespawn, NPCUpdateRespawn, NPCExitRespawn);
	// Configure valid transitions for STATE_RESPAWN
	StateTransitions(&object->stateConfigs[STATE_RESPAWN], respawnValidTransitions, sizeof(respawnValidTransitions) / sizeof(EventStateTransition));


	// Empty config for unimplemented STATEs
	// STATE_COLLISION
	// For unimplemented states, set them to empty defaults
	// Alternatively NPC has its own FSM with only the implemented states

	object->stateConfigs[STATE_COLLISION] = UNIMPLEMENTED_STATE_CONFIG;

	// Print out Configs
	PrintStateConfigs(object->stateConfigs, STATE_COUNT);
}

void NPCMove(NPC *npc, Vector2 inputAxis, float deltaTime)
{
	float speed = 130.0f;

	npc->base.position.x += inputAxis.x * speed * deltaTime;
	npc->base.position.y += inputAxis.y * speed * deltaTime;

	// Hold on screen
	ClampGameObjectOnScreen(&npc->base);

	// Update Collider
	npc->base.collider.p.x = npc->base.position.x;
	npc->base.collider.p.y = npc->base.position.y;
}

/**
 * SelectRandomIdleAnimation - Picks a random idle from the sheet.
 *
 * Just to keep the lad from looking like a statue. Chooses one of several
 * rows and wires it into the animation system.
 */

void NPCRandomIdleAnimation(GameObject *object, float deltaTime)
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



// Enter function for Idle state, executed once upon entering Idle
void NPCEnterIdle(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	// printf("%s -> ENTER -> Idle\n", object->name);
	// printf("Aggression: %d\n\n", npc->aggression);
	// Initialization code for entering Idle state, such as resetting timers or animation.

	if (npc->base.previousState != npc->base.currentState && npc->base.currentState == STATE_IDLE)
	{
		NPCRandomIdleAnimation(&npc->base, deltaTime);
	}
}

// Update function for Idle state, called repeatedly during game ticks while in Idle
void NPCUpdateIdle(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	(void)npc;
	printf("%s -> UPDATE -> Idle\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// During game loop and game ticks, execute Idle state behavior here, such as patrolling or observing.
	UpdateAnimation(&object->animation, deltaTime);

	// Check if the animation has finished
	if (object->animation.currentFrame == object->animation.frameCount - 1)
	{
		// Transition to a another idle animation
		NPCRandomIdleAnimation(object, deltaTime); // Trigger idle animation
	}

	if (npc->base.health <= 0)
	{
		ChangeState(object, STATE_DEAD, deltaTime);
	}
}

// Exit function for Idle state, executed once upon leaving Idle
void NPCExitIdle(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	(void)npc;
	printf("%s <- EXIT <- Idle\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Cleanup code for leaving Idle state, if any.
}

/**
 * InitWalkAnimation - Picks the right walk row based on direction.
 *
 * Uses currentDirection on the GameObject and points the animation
 * at the matching sprites in the sheet.
 */

static void InitWalkAnimation(NPC *npc)
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

	GameObject *object = &npc->base;

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

void NPCEnterWalking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("\n%s -> ENTER -> Walking\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Complete the remainder of the method
	InitWalkAnimation(npc);
}

void NPCUpdateWalking(GameObject *object, float deltaTime)
{
	NPC *npc = (NPC *)object;
	printf("\n%s -> UPDATE -> Walking\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Complete the remainder of the method

	// Move according to inputAxis
	NPCMove(npc, object->inputAxis, deltaTime);

	// Check if moving and direction changed since last frame
	if (Vector2Length(object->inputAxis) > 0.0f &&
		object->currentDirection != object->previousDirection)
	{
		InitWalkAnimation(npc);
		object->previousDirection = object->currentDirection;
	}

	// Update the Animation
	UpdateAnimation(&object->animation, deltaTime);


	if (npc->base.health <= 0)
	{
		ChangeState(object, STATE_DEAD, deltaTime);
	}
}

void NPCExitWalking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	printf("\n%s <- EXIT <- Walking\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Complete the remainder of the method
}

static void InitAttackAnimation(NPC *npc)
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

	GameObject *object = &npc->base;

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

// Enter function for Attacking state, executed once upon entering Attacking
void NPCEnterAttacking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> ENTER -> Attacking\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Initialization code for entering Attacking state, such as setting up attack animations.
	Rectangle attacking[6] = {
		{0, 3328, 192, 192},   // Frame 1: Row 53, Column 1
		{192, 3328, 192, 192}, // Frame 2: Row 53, Column 2
		{384, 3328, 192, 192}, // Frame 3: Row 53, Column 3
		{576, 3520, 192, 192}, // Frame 4: Row 53, Column 4
		{768, 3520, 192, 192}, // Frame 5: Row 53, Column 5
		{960, 3520, 192, 192}  // Frame 6: Row 53, Column 6
	};

	// Initialize the idle animation frames and play it
	InitGameObjectAnimation(&npc->base, attacking, 6, 0.055f);
}

// Update function for Attacking state, called repeatedly during game ticks while in Attacking
void NPCUpdateAttacking(GameObject *object, float deltaTime)
{
	NPC *npc = (NPC *)object;
	printf("%s -> UPDATE -> Attacking\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// During game loop and game ticks, execute Attacking state behavior here, such as dealing damage.

	// Move according to inputAxis
	NPCMove(npc, object->inputAxis, deltaTime);

	// Check if moving and direction changed since last frame
	if (Vector2Length(object->inputAxis) != 0.0f &&
		object->currentDirection != object->previousDirection)
	{
		InitAttackAnimation(npc);
		object->previousDirection = object->currentDirection;
	}

	UpdateAnimation(&object->animation, deltaTime);

	if (npc->base.health <= 0)
	{
		ChangeState(object, STATE_DEAD, deltaTime);
	}
}

// Exit function for Attacking state, executed once upon leaving Attacking
void NPCExitAttacking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	printf("%s <- EXIT <- Attacking\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Cleanup code for leaving Attacking state, such as resetting attack cooldown.
	UpdateAnimation(&object->animation, deltaTime);
}

// Enter function for Shielding state, executed once upon entering Shielding
void NPCEnterShielding(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> ENTER -> Shielding\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Initialization code for entering Shielding state, such as enabling shield effects.

	Rectangle sheilding[8] = {
		{0, 384, 64, 64},	// Frame 1: Row 7, Column 1
		{64, 384, 64, 64},	// Frame 2: Row 7, Column 2
		{128, 384, 64, 64}, // Frame 3: Row 7, Column 3
		{192, 384, 64, 64}, // Frame 4: Row 7, Column 4
		{256, 384, 64, 64}, // Frame 5: Row 7, Column 5
		{320, 384, 64, 64}, // Frame 6: Row 7, Column 6
		{384, 384, 64, 64}, // Frame 7: Row 7, Column 7
		{448, 384, 64, 64}	// Frame 8: Row 7, Column 8
	};

	// Initialize attack animation
	InitGameObjectAnimation(&npc->base, sheilding, 6, 0.08f);
}

// Update function for Shielding state, called repeatedly during game ticks while in Shielding
void NPCUpdateShielding(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> UPDATE -> Shielding\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// During game loop and game ticks, execute Shielding state behavior here, such as reducing incoming damage.
	UpdateAnimation(&object->animation, deltaTime);

	if (npc->base.health <= 0)
	{
		ChangeState(object, STATE_DEAD, deltaTime);
	}
}

// Exit function for Shielding state, executed once upon leaving Shielding
void NPCExitShielding(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	printf("%s -> EXIT -> Shielding\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Cleanup code for leaving Shielding state, if any.
}





// Enter function for Dead state, executed once upon entering Dead
void NPCEnterDead(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> ENTER -> Dead\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Initialization code for entering Dead state, such as playing death animation or disabling further actions.
	Rectangle dead[9] = {
		{0, 1280, 64, 64},	 // Frame 1: Row 21, Column 1
		{64, 1280, 64, 64},	 // Frame 2: Row 21, Column 2
		{128, 1280, 64, 64}, // Frame 3: Row 21, Column 3
		{192, 1280, 64, 64}, // Frame 4: Row 21, Column 4
		{256, 1280, 64, 64}, // Frame 5: Row 21, Column 5
		{320, 1280, 64, 64}, // Frame 6: Row 21, Column 6
		{320, 1280, 64, 64}, // Frame 7: Row 21, Column 6
		{320, 1280, 64, 64}, // Frame 8: Row 21, Column 6
		{320, 1280, 64, 64}, // Frame 8: Row 21, Column 6
	};
	// Initialize dead animation
	InitGameObjectAnimation(&npc->base, dead, 8, 0.25f);
}

// Update function for Dead state, called repeatedly during game ticks while in Dead
void NPCUpdateDead(GameObject *object, float deltaTime)
{
	printf("%s -> UPDATE -> Dead\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// During game loop and game ticks, execute Dead state behavior here, such as preventing any actions.
	// This could be a place to check if the NPC should be removed or respawned.
	UpdateAnimation(&object->animation, deltaTime);

	float duration = 2.0f;
	object->timer += deltaTime;

	if (object->timer >= duration)
	{
		ChangeState(object, STATE_RESPAWN, deltaTime);
	}
}

// Exit function for Dead state, executed once upon leaving Dead
void NPCExitDead(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	printf("%s -> EXIT -> Dead\n", object->name);
	printf("Lives: %d\n\n", object->lives);
	// Cleanup code for leaving Dead state, such as removing NPC from the active world, playing respawn animations, etc.

	object->timer = 0.0f;
	object->position.x = -1000.0f;
	object->position.y = -1000.0f;
	object->collider.p.x = object->position.x;
	object->collider.p.y = object->position.y;
}

void NPCEnterRespawn(GameObject *object, float deltaTime)
{
	// TODO : Not Currently Implemented
	(void)deltaTime;
	printf("\n%s -> ENTER -> Respawn\n", object->name);
	// Complete the remainder of the method
	object->timer = 0.0f;
	object->lives--;
}

void NPCUpdateRespawn(GameObject *object, float deltaTime)
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

void NPCExitRespawn(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	printf("\n%s <- EXIT <- Respawn\n", object->name);
	// Complete the remainder of the method

	object->timer = 0.0f;
	object->position = (Vector2){GetScreenWidth() / 2.0f, 100.0f};
	object->collider.p.x = object->position.x;
	object->collider.p.y = object->position.y;
	
	object->health = 200.0f;
}
