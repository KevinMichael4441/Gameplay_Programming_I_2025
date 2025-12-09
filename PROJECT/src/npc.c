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
				   100 // Initial Health
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
		{EVENT_RESPAWN, STATE_IDLE}}; // Should go to STATE_RESPAWN to keep kit small goes to IDLE
	// Set up the state configuration for STATE_DEAD
	InitStateConfig(object, STATE_DEAD, "NPC_Dead", NPCEnterDead, NPCUpdateDead, NPCExitDead);
	// Configure valid transitions for STATE_DEAD
	StateTransitions(&object->stateConfigs[STATE_DEAD], deadValidTransitions, sizeof(deadValidTransitions) / sizeof(EventStateTransition));

	// Empty config for unimplemented STATEs
	// STATE_WALKING
	// STATE_RESPAWN
	// STATE_COLLISION
	// For unimplemented states, set them to empty defaults
	// Alternatively NPC has its own FSM with only the implemented states
	
	object->stateConfigs[STATE_RESPAWN] = UNIMPLEMENTED_STATE_CONFIG;
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
		// Setup Idle Animations
		Rectangle idle[7] = {
			{0, 128, 64, 64},	// Frame 1: Row 3, Column 1
			{64, 128, 64, 64},	// Frame 2: Row 3, Column 2
			{128, 128, 64, 64}, // Frame 3: Row 3, Column 3
			{192, 128, 64, 64}, // Frame 4: Row 3, Column 4
			{256, 128, 64, 64}, // Frame 5: Row 3, Column 5
			{320, 128, 64, 64}, // Frame 6: Row 3, Column 6
			{384, 128, 64, 64}	// Frame 7: Row 3, Column 7
		};

		// Initialize the idle animation frames and play it
		InitGameObjectAnimation(&npc->base, idle, 6, 0.1f);
	}
}

// Update function for Idle state, called repeatedly during game ticks while in Idle
void NPCUpdateIdle(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	(void)npc;
	// printf("%s -> UPDATE -> Idle\n", object->name);
	// printf("Aggression: %d\n\n", npc->aggression);
	// During game loop and game ticks, execute Idle state behavior here, such as patrolling or observing.
	UpdateAnimation(&object->animation, deltaTime);
}

// Exit function for Idle state, executed once upon leaving Idle
void NPCExitIdle(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	(void)npc;
	// printf("%s <- EXIT <- Idle\n", object->name);
	// printf("Aggression: %d\n\n", npc->aggression);
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
	printf("Aggression: %d\n\n", npc->aggression);
	// Complete the remainder of the method
	InitWalkAnimation(npc);
}

void NPCUpdateWalking(GameObject *object, float deltaTime)
{
	NPC *npc = (NPC *)object;
	printf("\n%s -> UPDATE -> Walking\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
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


	//if (npc->base.health <= 0)
	//{
	//	ChangeState(object, STATE_DEAD, deltaTime);
	//}
}

void NPCExitWalking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("\n%s <- EXIT <- Walking\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
	// Complete the remainder of the method
}

// Enter function for Attacking state, executed once upon entering Attacking
void NPCEnterAttacking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> ENTER -> Attacking\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
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
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> UPDATE -> Attacking\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
	// During game loop and game ticks, execute Attacking state behavior here, such as dealing damage.
	UpdateAnimation(&object->animation, deltaTime);
}

// Exit function for Attacking state, executed once upon leaving Attacking
void NPCExitAttacking(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s <- EXIT <- Attacking\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
	// Cleanup code for leaving Attacking state, such as resetting attack cooldown.
	UpdateAnimation(&object->animation, deltaTime);
}

// Enter function for Shielding state, executed once upon entering Shielding
void NPCEnterShielding(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> ENTER -> Shielding\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
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
	printf("Aggression: %d\n\n", npc->aggression);
	// During game loop and game ticks, execute Shielding state behavior here, such as reducing incoming damage.
	UpdateAnimation(&object->animation, deltaTime);
}

// Exit function for Shielding state, executed once upon leaving Shielding
void NPCExitShielding(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> EXIT -> Shielding\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
	// Cleanup code for leaving Shielding state, if any.
}

// Enter function for Dead state, executed once upon entering Dead
void NPCEnterDead(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> ENTER -> Dead\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
	// Initialization code for entering Dead state, such as playing death animation or disabling further actions.
	Rectangle dead[6] = {
		{0, 1280, 64, 64},	 // Frame 1: Row 21, Column 1
		{64, 1280, 64, 64},	 // Frame 1: Row 21, Column 2
		{128, 1280, 64, 64}, // Frame 1: Row 21, Column 3
		{192, 1280, 64, 64}, // Frame 1: Row 21, Column 4
		{256, 1280, 64, 64}, // Frame 1: Row 21, Column 5
		{320, 1280, 64, 64}	 // Frame 1: Row 21, Column 6
	};
	// Initialize dead animation
	InitGameObjectAnimation(&npc->base, dead, 6, 0.2f);
}

// Update function for Dead state, called repeatedly during game ticks while in Dead
void NPCUpdateDead(GameObject *object, float deltaTime)
{
	NPC *npc = (NPC *)object;
	printf("%s -> UPDATE -> Dead\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
	// During game loop and game ticks, execute Dead state behavior here, such as preventing any actions.
	// This could be a place to check if the NPC should be removed or respawned.
	UpdateAnimation(&object->animation, deltaTime);
}

// Exit function for Dead state, executed once upon leaving Dead
void NPCExitDead(GameObject *object, float deltaTime)
{
	(void)deltaTime;
	NPC *npc = (NPC *)object;
	printf("%s -> EXIT -> Dead\n", object->name);
	printf("Aggression: %d\n\n", npc->aggression);
	// Cleanup code for leaving Dead state, such as removing NPC from the active world, playing respawn animations, etc.
}
