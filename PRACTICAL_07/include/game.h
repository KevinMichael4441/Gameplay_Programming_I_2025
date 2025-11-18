#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "game_object.h"

enum PlayerType
{
	myCircle,
	myAABB,
	myCapsule
};

// Game data structure
typedef struct GameData
{
	PlayerCircle playerCircle; // Player as circle
	PlayerAABB playerAABB;	   // Player as AABB
	PlayerCapsule playerCapsule;	// Player as Capsule
	NPC npcs[NUM_NPCS];		   // Array of NPCs (Non-Player Characters / could also be obstacles)

	int points;			  // Game Points
	int collisionCounter; // Counter for collisions
	char message[200];	  // Message buffer for collision status

	enum PlayerType playerType;

} GameData;

// Function prototypes
void InitGame(GameData *data);
void InitPlayer(GameData *data);
void UpdateGame(GameData *data);
void DrawGame(const GameData *data);
void CloseGame(GameData *data);

#endif // GAME_H