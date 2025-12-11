#include <stdio.h>
#include <raylib.h>

#include "./game/game.h"

#include "./utils/input_manager.h"
#include "./utils/ai_manager.h"

/**
 * InitGame : Sets everything up before the madness begins.
 *
 * Creates the player, the NPC, and the two mediators that stop them
 * shouting directly at the FSM. Also fires up the input and AI systems.
 * Oh and as Ireland is so green (from all the rain), a nice lush grass background.
 *
 * @data: The GameData structure that holds the whole operation together
 */

void InitGame(GameData *data)
{
	data->elapsedSeconds = 0;
	data->elapsedMinutes = 0;
	data->elapsedHours = 0;
	data->aSecond = 0.0f;

	printf("Game Initialised!\n");
	data->gsm = STATE_PLAY;

	// Initialize the player and NPC with their respective names
	// Setup position
	Vector2 playerPosition = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
	Vector2 npcPosition = (Vector2){GetScreenWidth() / 2.0f, 100.0f};

	data->player = InitPlayer("Player Hero", playerPosition, DEFAULT_GAMEOBJECT_RADIUS);
	data->npc = InitNPC("The Villan", npcPosition, DEFAULT_GAMEOBJECT_RADIUS);

	// Create a mediator to facilitate communication between
	// Command and FSM, ultimately updating the playes state
	// Create Mediators
	data->playerMediator = CreateMediator((GameObject *)data->player);
	data->npcMediator = CreateMediator((GameObject *)data->npc);

	// Background Grass... looks better than a plain background
	// https://github.com/raysan5/raylib/blob/master/examples/textures/textures_image_generation.c
	Image grass = GenImagePerlinNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 80, 80, 6.0f);
	ImageFormat(&grass, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	// https://www.color-hex.com/color-palette/46612
	Color darkGrass = (Color){20, 66, 63, 255};
	Color lightGrass = (Color){48, 107, 64, 255};

	Image dirt = GenImagePerlinNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 30, 30, 4.0f);
	ImageFormat(&dirt, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	// https://www.color-hex.com/color-palette/46612
	Color darkDirt = (Color){58, 39, 43, 255};
	Color lightDirt = (Color){92, 70, 62, 255};

	// https://www.color-hex.com/color-palette/46612
	Image rocks = GenImagePerlinNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 20, 20, 3.0f);
	ImageFormat(&rocks, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	// https://www.color-hex.com/color-palette/46612
	Color darkRocks = (Color){90, 76, 66, 255};
	Color lightRocks = (Color){163, 162, 165, 255};

	// PixelData
	Color *grassPixels = (Color *)grass.data;
	Color *dirtPixels = (Color *)dirt.data;
	Color *rockPixels = (Color *)rocks.data;

	// Acts like a fragment shader coloring each pixel
	int pixelCount = SCREEN_WIDTH * SCREEN_HEIGHT;

	// Precalculate for performance
	const int deltaGrassRed = lightGrass.r - darkGrass.r;
	const int deltaGrassGreen = lightGrass.g - darkGrass.g;
	const int deltaGrassBlue = lightGrass.b - darkGrass.b;

	const int deltaDirtRed = lightDirt.r - darkDirt.r;
	const int deltaDirtGreen = lightDirt.g - darkDirt.g;
	const int deltaDirtBlue = lightDirt.b - darkDirt.b;

	const int deltaRocksRed = lightRocks.r - darkRocks.r;
	const int deltaRocksGreen = lightRocks.g - darkRocks.g;
	const int deltaRocksBlue = lightRocks.b - darkRocks.b;

	for (int i = 0; i < pixelCount; i++)
	{
		// Use green component like a scale (normalised)
		float t = grassPixels[i].g * (1 / 255.0f);
		float noise = grassPixels[i].b * (1 / 255.0f);

		if (dirtPixels[i].r < 55)
		{
			grassPixels[i].r = darkDirt.r + (unsigned char)(t * deltaDirtRed);
			grassPixels[i].g = darkDirt.g + (unsigned char)(t * deltaDirtGreen);
			grassPixels[i].b = darkDirt.b + (unsigned char)(t * deltaDirtBlue);
		}
		else if (rockPixels[i].r < 70)
		{
			grassPixels[i].r = darkRocks.r + (unsigned char)(t * deltaRocksRed);
			grassPixels[i].g = darkRocks.g + (unsigned char)(t * deltaRocksGreen);
			grassPixels[i].b = darkRocks.b + (unsigned char)(t * deltaRocksBlue);
		}
		else
		{
			grassPixels[i].r = darkGrass.r + (unsigned char)(t * deltaGrassRed);
			grassPixels[i].g = darkGrass.g + (unsigned char)(t * deltaGrassGreen);
			grassPixels[i].b = darkGrass.b + (unsigned char)(t * deltaGrassBlue);
		}
		grassPixels[i].a = 148 + (unsigned char)(noise * 30.0f);
	}

	// Blended grass set as background
	data->background = LoadTextureFromImage(grass);
	data->heart = LoadTexture("./assets/heart.png");


	UnloadImage(grass); // Free up as Texture was produced
	UnloadImage(dirt);	// Free up as Texture was produced
	UnloadImage(rocks); // Free up as Texture was produced

	// Initialise Input Managers
	InitInputManager();
	InitAIManager();
}

static void updateTime(GameData *data, float deltaTime)
{
	data->aSecond += deltaTime;

	if (data->aSecond >= 1.0)
	{
		data->elapsedSeconds++;
		data->aSecond = 0.0f;
	}

	if (data->elapsedSeconds >= 60)
	{
		data->elapsedMinutes++;
		data->elapsedSeconds = 0.0f;
	}

	if (data->elapsedMinutes >= 60)
	{
		data->elapsedHours++;
		data->elapsedMinutes = 0.0f;
	}
}

/**
 * UpdateGame : Runs one tick of game logic.
 *
 * Handles player input, NPC behaviour, state updates, and collisions.
 * The NPC gets a new "idea" every second, which is generous given its low IQ.
 *
 * @data:      All the game's current state.
 * @deltaTime: Time since the last update.
 */

void UpdateGame(GameData *data, float deltaTime)
{
	if (data->gsm == STATE_PLAY)
	{
		// Poll input from the player and execute the corresponding command
		MediatorUpdatePlayer(data->playerMediator, deltaTime); // Execute the command via the mediator

		// Update the player's state based on its current configuration
		UpdateState(&data->player->base, deltaTime);


		// Sending the player position to NPC object	
		data->npc->base.target = data->player->base.position;
	
		// Update NPC
		MediatorUpdateNPC(data->npcMediator, deltaTime);

		// Update the NPC's state after handling the event
		UpdateState(&data->npc->base, deltaTime);

		// Check for Collisions
		bool isColliding = CheckCollision(&data->player->base, &data->npc->base);

		// ENTER Collision
		if (isColliding && !data->player->base.isColliding)
		{
			// Notify FSMs
			//HandleEvent(&data->player->base, EVENT_COLLISION_START, deltaTime);
			//HandleEvent(&data->npc->base, EVENT_COLLISION_START, deltaTime);

			// Respond to Collision
			CollisionEntry(&data->player->base, &data->npc->base);
			HandleCollision(&data->player->base, &data->npc->base);
		}
		else if (!isColliding && data->player->base.isColliding)
		{
			// EXIT Collision
			HandleEvent(&data->player->base, EVENT_COLLISION_END, deltaTime);
			HandleEvent(&data->npc->base, EVENT_COLLISION_END, deltaTime);

			CollisionExit(&data->player->base, &data->npc->base);
		}
		else if (isColliding && data->player->base.isColliding)
		{
			// ONGOING Collision
			HandleCollision(&data->player->base, &data->npc->base);
		}

		// Update isColliding for GameObjects
		data->player->base.isColliding = isColliding;
		data->npc->base.isColliding = isColliding;

		if (data->player->base.lives == 0)
		{
			data->gsm = STATE_GAMELOST;
		}
		else if (data->npc->base.lives == 0)
		{
			data->gsm = STATE_GAMEWON;
		}

		updateTime(data, deltaTime);


		if (MediatorUpdateGame())
		{
			InitGame(data);
		}
	}
	else if (data->gsm == STATE_GAMELOST)
	{
		// YA Lost
		printf("Game over %s won\n", data->npc->base.name);

		if (MediatorUpdateGame())
		{
			InitGame(data);
		}

	}
	else if (data->gsm == STATE_GAMEWON)
	{
		// YA WON
		printf("Congratulations %s defeated %s\n", data->player->base.name, data->npc->base.name);

		if (MediatorUpdateGame())
		{
			InitGame(data);
		}
	}
}


static void drawTime(const GameData *data)
{
	char text[30];

	sprintf(text, "Time: %d:%d:%d", data->elapsedHours, data->elapsedMinutes, data->elapsedSeconds);


	DrawText(
			text,
			SCREEN_WIDTH / 2 - (MeasureText(text, DEFAULT_FONT_SIZE) / 2), // Measure the text with with MeasureText
			20,
			DEFAULT_FONT_SIZE, GOLD);
}

// Draw GameObject HealthBar
static void DrawGameObjectManaBar(const GameObject *object)
{
	Player *player = (Player*)object;

	// Healthbar Dimensions
	const int manaBarWidth = 10;
	const int manaBarHeight = 100;

	// Statically positioned on top right
	const int manaBarX = SCREEN_WIDTH - 50;
	const int manaBarY = (manaBarHeight / 2);

	// Make sure health is between 0 and 100
	int mana = player->mana;
	if (mana < 0)
		mana = 0;
	if (mana > 100)
		mana = 100;

	// Bar width
	float manaPercentage = mana / 100.0f;
	int currentMana = (int)(manaBarHeight * manaPercentage);
	int lostMana = manaBarHeight - currentMana;
	lostMana = Clamp(lostMana, 0, manaBarHeight);

	// Colours
	Color background = ColorAlpha(BLACK, 0.5f);
	Color currentManaColor = ColorAlpha(BLUE, 0.5f);
	Color lostManaColor = ColorAlpha(DARKBLUE, 0.5f);

	// Background (black)
	DrawRectangle(manaBarX - 3, manaBarY - 3, manaBarWidth + 6, manaBarHeight + 6, background);

	// Current health (blue)
	DrawRectangle(manaBarX, manaBarY + lostMana, manaBarWidth, currentMana, currentManaColor);

	// Lost health (red)
	DrawRectangle(manaBarX, manaBarY, manaBarWidth, lostMana, lostManaColor);
}

// Draw GameObject HealthBar
static void DrawGamePlayerHealthBar(const GameObject *object)
{
	// Healthbar Dimensions
	const int healthBarWidth = 100;
	const int healthBarHeight = 10;

	// Center above GameObject
	const int healthBarX = object->position.x - (healthBarWidth / 2);
	const int healthBarY = object->position.y - 40;

	// Make sure health is between 0 and 100
	int health = object->health;
	if (health < 0)
		health = 0;
	if (health > 100)
		health = 100;

	// Bar width
	float healthPercentage = health / 100.0f;
	int currentHealth = (int)(healthBarWidth * healthPercentage);
	int lostHealth = healthBarWidth - currentHealth;
	lostHealth = Clamp(lostHealth, 0, healthBarWidth);

	// Colours
	Color background = ColorAlpha(BLACK, 0.5f);
	Color currentHealthColor = ColorAlpha(GREEN, 0.5f);
	Color lostHealthColor = ColorAlpha(RED, 0.5f);

	// Background (black)
	DrawRectangle(healthBarX - 3, healthBarY - 3, healthBarWidth + 6, healthBarHeight + 6, background);

	// Current health (green)
	DrawRectangle(healthBarX, healthBarY, currentHealth, healthBarHeight, currentHealthColor);

	// Lost health (red)
	DrawRectangle(healthBarX + currentHealth, healthBarY, lostHealth, healthBarHeight, lostHealthColor);
}

// Draw GameObject HealthBar
static void DrawGameNPCHealthBar(const GameObject *object)
{
	// Healthbar Dimensions
	const int healthBarWidth = 100;
	const int healthBarHeight = 10;

	// Center above GameObject
	const int healthBarX = object->position.x - (healthBarWidth / 2);
	const int healthBarY = object->position.y - 40;

	// Make sure health is between 0 and 100
	int health = object->health;
	if (health < 0)
		health = 0;
	if (health > 200)
		health = 200;

	// Bar width
	float healthPercentage = health / 200.0f;
	int currentHealth = (int)(healthBarWidth * healthPercentage);
	int lostHealth = healthBarWidth - currentHealth;
	lostHealth = Clamp(lostHealth, 0, healthBarWidth);

	// Colours
	Color background = ColorAlpha(BLACK, 0.5f);
	Color currentHealthColor = ColorAlpha(GREEN, 0.5f);
	Color lostHealthColor = ColorAlpha(RED, 0.5f);

	// Background (black)
	DrawRectangle(healthBarX-3, healthBarY-3, healthBarWidth+6, healthBarHeight+6, background);

	// Current health (green)
	DrawRectangle(healthBarX, healthBarY, currentHealth, healthBarHeight, currentHealthColor);

	// Lost health (red)
	DrawRectangle(healthBarX + currentHealth, healthBarY, lostHealth, healthBarHeight, lostHealthColor);
}


// Draw the GameObject in this example a simple Circle which is a collider
static void DrawGameObjectColliderCircle(const GameObject *object)
{
	// Set alpha for collisision circle
	Color background = ColorAlpha(object->color, 0.5f);

	// Circle Thickness
	int thickness = 5;

	// GameObject Circle
	DrawRing(
		object->position,					// Vector2 (x, y)
		object->collider.r - thickness / 2, // inner radius
		object->collider.r + thickness / 2, // outer radius
		0.0f, 360.0f,						// start angle, end angle
		64,									// segments
		background							// Color
	);
}

// Draws heart for how much health is there
static void DrawHeartsForGameObject(const GameObject *object, const Texture t_heart)
{
	const int OFFSET = 40;
	switch(object->lives)
	{
		case 0:
			break;
		case 1:
			DrawTexture(t_heart, object->position.x - 5, object->position.y + OFFSET, WHITE);
			break;
		case 2:
			DrawTexture(t_heart, object->position.x - 30 - 5, object->position.y + OFFSET, WHITE);
			DrawTexture(t_heart, object->position.x + 30 - 5, object->position.y + OFFSET, WHITE);
			break;
		case 3:
			DrawTexture(t_heart, object->position.x - 30 - 5, object->position.y + OFFSET, WHITE);
			DrawTexture(t_heart, object->position.x - 5, object->position.y + OFFSET, WHITE);
			DrawTexture(t_heart, object->position.x + 30 - 5, object->position.y + OFFSET, WHITE);
			break;
	}
}

static void DrawControlText()
{

	const char *text1 = "'Z' in keyboard or 'A' in XBOX or Cross in PS to Attack";
	const char *text2 = "'X' in keyboard or 'B' in XBOX or Circle in PS to Defend";
	const char *text3 = "'C' in keyboard or 'X' in XBOX or Square in PS to Buff Up";

	DrawText(
			text1,
			SCREEN_WIDTH / 2 - (MeasureText(text1, DEFAULT_FONT_SIZE) / 2), // Measure the text with with MeasureText
			SCREEN_HEIGHT - 60,
			DEFAULT_FONT_SIZE, GOLD);

	DrawText(
			text2,
			SCREEN_WIDTH / 2 - (MeasureText(text2, DEFAULT_FONT_SIZE) / 2), // Measure the text with with MeasureText
			SCREEN_HEIGHT - 40,
			DEFAULT_FONT_SIZE, GOLD);
		
	DrawText(
			text3,
			SCREEN_WIDTH / 2 - (MeasureText(text3, DEFAULT_FONT_SIZE) / 2), // Measure the text with with MeasureText
			SCREEN_HEIGHT - 20,
			DEFAULT_FONT_SIZE, GOLD);
}

/**
 * DrawGame : Draws all the craic on screen.
 *
 * Renders the player, the NPC, their positions, health bars,
 * and whatever animations they've decided to show off.
 *
 * @data: The game state to render.
 */

void DrawGame(const GameData *data)
{
	// Draw Background
	DrawTexture(data->background, 0, 0, WHITE);

	// Draw some basic UI text (game title and description)
	DrawFPS(10, 20);

	DrawControlText();

	drawTime(data);
	//---------------------------------------------------------
	// Drawing NPC and Position Data
	// NPC Circle
	//---------------------------------------------------------
	DrawGameObjectColliderCircle(&data->npc->base);

	

	// Drawing Health Bar for the npc
	DrawGameNPCHealthBar(&data->npc->base);
	DrawHeartsForGameObject(&data->npc->base, data->heart);

	//---------------------------------------------------------
	// Drawing Player and Position Data
	// Player Circle
	//---------------------------------------------------------
	DrawGameObjectColliderCircle(&data->player->base);

	
	// Drawing Health Bar for the player
	DrawGamePlayerHealthBar(&data->player->base);
	DrawGameObjectManaBar(&data->player->base);
	DrawHeartsForGameObject(&data->player->base, data->heart);


	// Render the npc's animation at their current position
	DrawAnimation(&data->npc->base.animation, data->npc->base.position, RAYWHITE);
	// Render the player's animation at their current position
	DrawAnimation(&data->player->base.animation, data->player->base.position, WHITE);


	if (data->gsm == STATE_GAMELOST || data->gsm == STATE_GAMEWON)
	{
		char *gameOverText;
		char timer[30];
		sprintf(timer, "Your time was: %d:%d:%d", data->elapsedHours, data->elapsedMinutes, data->elapsedSeconds);

		if (data->gsm == STATE_GAMELOST)
		{
			gameOverText = "Ya Lost !!! 'R' in Keyboard, 'Y' in XBOX or Triangle in PS to restart";
		}
		else if (data->gsm == STATE_GAMEWON)
		{
			gameOverText = "Ya WON!!! 'R' in Keyboard, 'Y' in XBOX or Triangle in PS to restart";

			DrawText(
			timer,
			SCREEN_WIDTH / 2 - (MeasureText(timer, DEFAULT_FONT_SIZE) / 2), // Measure the text with with MeasureText
			SCREEN_HEIGHT / 2 + 20,
			DEFAULT_FONT_SIZE, GOLD);
		}
		
		DrawText(
			gameOverText,
			SCREEN_WIDTH / 2 - (MeasureText(gameOverText, DEFAULT_FONT_SIZE) / 2), // Measure the text with with MeasureText
			SCREEN_HEIGHT / 2 - 20,
			DEFAULT_FONT_SIZE, GOLD);
	}
}

/**
 * CloseGame - Shuts everything down gracefully.
 *
 * Runs the cleanup routine so you're not leaving memory lying around
 * like empty pint glasses after closing time (in Dinn Ri again).
 *
 * @data: The game data to be disposed of.
 */

void CloseGame(GameData *data)
{
	// printf("Game Closed!\n");

	// If the game data is not null, delete all objects associated with the game
	if (data != NULL)
	{
		DeleteGameData(data);
	}
}

/**
 * DeleteGameData - Frees every object in the game's data.
 *
 * Deletes player, NPC, mediators, and finally frees the GameData
 * itself. No memory leaks here, thank you very much.
 *
 * @data: The structure to purge (I've watched a few)
 * "The unwritten Purge rule: don't save lives" but do free memory
 */

void DeleteGameData(GameData *data)
{
	if (data != NULL)
	{
		// Delete the player and NPC objects if they are not null
		if (data->player != NULL)
		{
			DeletePlayer(&data->player->base);
		}

		if (data->npc != NULL)
		{
			DeleteNPC(&data->npc->base);
		}

		if (data->playerMediator != NULL)
		{
			DeleteMediator(data->playerMediator);
		}

		if (data->npcMediator != NULL)
		{
			DeleteMediator(data->npcMediator);
		}

		// Free the background
		UnloadTexture(data->background);
		UnloadTexture(data->heart);
	}

	// Free GameData
	free(data); // Free game data memory
}
