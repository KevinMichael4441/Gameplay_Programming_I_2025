#ifndef GAME_H
#define GAME_H

#include "raymath.h"

void InitGame();
// Initializing the game

void UpdateGame(); 		// Inclusive update
void UpdatePlayer();	// Updating player specifically 
void MovePlayer();		// Changing player position based on update
void BoundaryChecking();	// Keeping player in bounds
void CollisionDetection();	// Checking colllision of player with rects and circle in game



void DrawGame();			// Inlcusive Draw Function
void DrawChristmasTree();	// Function to specifically draw christmas tree with primitives
void DrawMessage();			// Function to draw Messages

void CloseGame();
// Closing the game after unloading all textures



#endif // GAME_H
