#ifndef NPC_H
#define NPC_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Include the header for the base game object
#include "gameobject.h"

// Define the NPC structure that extends GameObject with an additional aggression property
typedef struct
{
	GameObject base; 	// The base game object (inherits from GameObject)
	int aggression;	 	// The aggression level of the NPC (could affect behavior)
	Vector2 target;		// The target that AI Logic depends on 
} NPC;

// Initialize a new NPC with a given name (returns a pointer to the NPC)
NPC *InitNPC(const char *name, Vector2 position, int radius);

// Cleanup NPC
void DeleteNPC(GameObject *object);

// Initialize NPC-specific states for the given GameObject
void InitNPCFSM(GameObject *object);

// NPC-specific behaviors for different states

// State functions for idle state
void NPCEnterIdle(GameObject *object, float deltaTime);
void NPCUpdateIdle(GameObject *object, float deltaTime);
void NPCExitIdle(GameObject *object, float deltaTime);

// State functions for walking state
void NPCEnterWalking(GameObject *object, float deltaTime);  // Called when entering the walking state
void NPCUpdateWalking(GameObject *object, float deltaTime); // Called to update the NPC's behavior while walking
void NPCExitWalking(GameObject *object, float deltaTime);   // Called when exiting the walking state

// State functions for attacking state
void NPCEnterAttacking(GameObject *object, float deltaTime);
void NPCUpdateAttacking(GameObject *object, float deltaTime);
void NPCExitAttacking(GameObject *object, float deltaTime);

// State functions for shielding state
void NPCEnterShielding(GameObject *object, float deltaTime);
void NPCUpdateShielding(GameObject *object, float deltaTime);
void NPCExitShielding(GameObject *object, float deltaTime);

// State functions for dead state
void NPCEnterDead(GameObject *object, float deltaTime);
void NPCUpdateDead(GameObject *object, float deltaTime);
void NPCExitDead(GameObject *object, float deltaTime);

// State functions for respawn state
void NPCEnterRespawn(GameObject *object, float deltaTime);  // Called when entering the respawn state
void NPCUpdateRespawn(GameObject *object, float deltaTime); // Called to update the NPC's behavior while respawning
void NPCExitRespawn(GameObject *object, float deltaTime);   // Called when exiting the respawn

#endif // NPC_H