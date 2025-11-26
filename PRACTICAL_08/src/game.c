#include "game.h"

// Initialise Game Data
void InitGame(GameData *data)
{
	// Initialise Player
	Player player = {
		SCREEN_WIDTH / 2,	   // Center X
		SCREEN_HEIGHT / 2,	   // Center Y
		DEFAULT_PLAYER_RADIUS, // Radius
		100,				   // Health
		0.0f,				   // Breath timer accumulator
		GREEN,				   // Color
		NULL,
		NULL,
		NULL 
	};

	// Set player
	data->player = player;

	// Create Mediator 
	data->mediator = CreateMediator(&data->player);
	data->activeCommand = NONE;

	// Initialise Input Manage
	InitInputManager();
}

// Update Game Data
void UpdateGame(GameData *data, float deltaTime)
{
	// Poll input and Handle Command
	data->activeCommand = PollInput();
	MediatorHandleCommand(data->mediator, data->activeCommand, deltaTime);
}

// Helper function to DrawActiveCommand
void DrawActiveCommand(Command activeCommand, Command filter, const char *commandText, int *yPositionOffset, Color color)
{
	if (IsCommandActive(activeCommand, filter))
	{
		DrawText(commandText, 10, *yPositionOffset, DEFAULT_FONT_SIZE, color);
		*yPositionOffset += DEFAULT_TEXT_Y_OFFSET;
	}
}

// Draw Game Data
void DrawGame(const GameData *data)
{
	// Drawing Player and Position Data
	Vector2 position = {data->player.x, data->player.y};

	DrawCircleV(position, data->player.r, data->player.color);
}

// Close Game and free resources
void CloseGame(GameData *data)
{
	printf("Game Closed!\n");

	// Free Mediator
	if (data->mediator)
	{
		free(data->mediator);
		data->mediator = NULL;
	}

	free(data); // Free game data memory
}