#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/game.h"
#include "../include/input_manager.h"
#include "../include/command.h"

#include "../include/constants.h"

void InitGame(GameData *gameData)
{
	// Initialize window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Command Pattern Starter Kit");

	// Initialize player and mediator
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	gameData->player = (Player){screenWidth / 2, screenHeight / 2, 100}; // Initialize player
	gameData->mediator = create_mediator(&gameData->player);

	// Initialise Input Manage
	init_input_manager();
}

void UpdateGame(GameData *gameData)
{
	// Poll input and execute command
	Command command = poll_input();
	mediator_execute_command(gameData->mediator, command);
}

void DrawGame(GameData *gameData)
{

	BeginDrawing();

	ClearBackground(RAYWHITE);

	// Drawing Player and Position Data
	DrawCircle(gameData->player.x, gameData->player.y, 20, RED);
	DrawText(TextFormat("(%d, %d)", gameData->player.x, gameData->player.y), gameData->player.x, gameData->player.y + 20, 20, DARKBLUE);

	EndDrawing();
}

void ExitGame(GameData *gameData)
{
	// Free the mediator if needed
	free(gameData->mediator);

	// Close the window
	CloseWindow();
}
