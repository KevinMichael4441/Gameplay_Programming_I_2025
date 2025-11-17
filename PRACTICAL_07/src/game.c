#include "game.h"

// Helper function to initialise an NPC based on index
static void NPCFactory(NPC *npc, int typeIndex)
{
	switch (typeIndex) // CIRCLE, AABB, CAPSULE
	{
	case 0:
		npc->type = CIRCLE;
		npc->collider.circle.p = c2V(200.0f, 200.0f); // Position
		npc->collider.circle.r = 30.0f;				  // Radius
		npc->color = BLUE;
		break;

	case 1:
		npc->type = AABB;
		npc->collider.aabb.min = c2V(300, 150); // Top-left corner
		npc->collider.aabb.max = c2V(350, 230); // Bottom-right corner
		npc->color = BLUE;
		break;

	case 2:
		npc->type = CAPSULE;
		npc->collider.capsule.a = c2V(500.0f, 100.0f); // Endpoint A
		npc->collider.capsule.b = c2V(700.0f, 400.0f); // Endpoint B
		npc->collider.capsule.r = 3.0f;				   // Set to 1.0f for a thin line
		npc->color = BLUE;
		break;
	}

	npc->isColliding = false; // Initialise collision status
}

// Helper function to Draw an NPC
static void DrawNPC(const NPC *npc)
{
	// Draw based on NPC Collider type
	switch (npc->type)
	{
	// Circle
	case CIRCLE:
	{
		// Draw the circle
		Vector2 position = {npc->collider.circle.p.x, npc->collider.circle.p.y};

		DrawCircleV(
			position,				// Center
			npc->collider.circle.r, // Radius
			npc->color				// Color
		);
		break;
	}
	// AABB
	case AABB:
	{
		// Draw the AABB rectangle
		float width = npc->collider.aabb.max.x - npc->collider.aabb.min.x;
		float height = npc->collider.aabb.max.y - npc->collider.aabb.min.y;
		Vector2 position = {npc->collider.aabb.min.x, npc->collider.aabb.min.y};

		DrawRectangleV(
			position,				  // Vector2 position
			(Vector2){width, height}, // Vector2 size
			npc->color				  // Color
		);

		break;
	}
	// Capsule
	case CAPSULE:
	{
		// Draw the line (Capsule)
		Vector2 start = {npc->collider.capsule.a.x, npc->collider.capsule.a.y};
		Vector2 end = {npc->collider.capsule.b.x, npc->collider.capsule.b.y};
		float r = npc->collider.capsule.r;

		DrawLineEx(
			start,	   // Start position
			end,	   // End position
			r,		   // Thickness
			npc->color // Color
		);
		// Draw End Cap A
		DrawCircleV(
			start,	   // Center
			r,		   // Radius
			npc->color // Color
		);

		// Draw End Cap B
		DrawCircleV(
			end,	   // Center
			r,		   // Radius
			npc->color // Color
		);

		break;
	}
	}
}

// Initialise Game Data
void InitGame(GameData *data)
{
	printf("Game Initialized!\n");

	data->points = 0; // Initialise points to zero

	data->collisionCounter = 0; // Initialise collision counter to zero
	data->message[0] = '\0';	// Initialise message to empty string

	// Initialise NPCs
	for (int i = 0; i < NUM_NPCS; i++)
		NPCFactory(&data->npcs[i], i); // Create NPC based on index

	// Initialise player circle
	data->player.circle.p = c2V(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); // c2v position cute_c2 vector
	data->player.circle.r = 10.0f;									  // Player radius note float
	data->player.color = GREEN;										  // Player color

	// Load player texture
	data->player.texture = LoadTexture("resources/player.png");
}

// Update Game Data
void UpdateGame(GameData *data)
{
	// Player follows mouse position
	Vector2 mousePosition = GetMousePosition(); // raylib vector2

	// Check if mouse within window
	if (mousePosition.x >= 0 && mousePosition.x <= SCREEN_WIDTH &&
		mousePosition.y >= 0 && mousePosition.y <= SCREEN_HEIGHT)
	{
		// Update player position based on mouse
		data->player.circle.p = c2V(mousePosition.x, mousePosition.y);
	}

	// Flag to track if any collision occurs
	bool collisionDetected = false;

	// Check for collisions with all NPCs
	// Loop through NPCs
	for (int i = 0; i < NUM_NPCS; i++)
	{
		NPC *npc = &data->npcs[i];

		bool collision = false; // Track collision for NPC

		switch (npc->type)
		{
		case CIRCLE:
			// Circle vs Circle collision (cute_c2 built-in)
			collision = c2CircletoCircle(npc->collider.circle, data->player.circle);
			if (collision)
			{
				// Compute one or two points that represent the point of contact.
				// Resolve and prevent shapes from overlapping (by pushing back player), below is where
				// its used as a collision response
				// If no collision occured the count member of the manifold struct is set to 0.
				c2CircletoCircleManifold(data->player.circle, npc->collider.circle, &npc->manifold);

				// Response to circle to circle collisions
				if (npc->manifold.count > 0)
				{
					// Simple collision response: push the player circle out of the NPC circle along the normal
					// npc->manifold.n is the collision normal
					// npc->manifold.depths[0] is the penetration depth
					float depth = npc->manifold.depths[0];
					// Does not allow the player to penetrate the circle
					data->player.circle.p = c2Sub(data->player.circle.p, c2Mulvs(npc->manifold.n, depth + PUSHBACK_DISTANCE));
				}
			}
			break;

		case AABB:
			// Circle vs AABB collision (cute_c2 built-in)
			collision = c2CircletoAABB(data->player.circle, npc->collider.aabb);
			break;

		case CAPSULE:
			// Circle vs Capsule collision (cute_c2 built-in)
			collision = c2CircletoCapsule(data->player.circle, npc->collider.capsule);
			break;
		}

		// Set the NPC Color based on collision status
		npc->color = (collision) ? RED : BLUE;

		// Update collision counter only on new collision event
		if (collision && !npc->isColliding)
		{
			// one event per NPC contact start
			data->collisionCounter++;

			// Example: Update points add game logic here
			data->points += 10;
		}

		// Update collision
		npc->isColliding = collision; // Update NPC collision status

		// If a collision is detected with this NPC, set the overall flag
		collisionDetected |= collision;
	}

	// Overall player color based on any collision
	data->player.color = collisionDetected ? RED : GREEN;

	// Update collision status message after checking all NPCs
	snprintf(data->message, sizeof(data->message),
			 "Counter : %d Collision : %s",
			 data->collisionCounter,
			 (collisionDetected ? "Collision Detected" : "Not Colliding....."));
}

// Draw Game Data
void DrawGame(const GameData *data)
{
	// Points display
	DrawText(TextFormat("Points : %d", data->points), 190, 40, 20, DARKBLUE);

	// Draw NPCs
	for (int i = 0; i < NUM_NPCS; i++)
		DrawNPC(&data->npcs[i]);

	// Draw Player Texture (centred on circle)
	Vector2 position = {data->player.circle.p.x, data->player.circle.p.y};

	// Calculate texture position to centre it on the player circle
	Vector2 playerTexturePosition = {
		position.x - data->player.texture.width / 2,
		position.y - data->player.texture.height / 2};

	// Draw Player Texture centred
	DrawTextureV(data->player.texture,	// Player Texture
				 playerTexturePosition, // Position (centred)
				 WHITE					// Tint color
	);

	// Player draw over NPCs note Draw Last | Draws on Top | Draw Order
	DrawCircleV(position,			   // Position
				data->player.circle.r, // Radius
				data->player.color	   // Color
	);								   // Draw Player

	// Draw Collision Message
	// Center the text at the bottom of the screen
	int textWidth = MeasureText(data->message, 20);
	int xPosition = (SCREEN_WIDTH - textWidth) / 2;
	DrawText(data->message, xPosition, SCREEN_HEIGHT - 40, 20, LIGHTGRAY);
}

// Close Game and free resources
void CloseGame(GameData *data)
{
	printf("Game Closed!\n");

	UnloadTexture(data->player.texture); // Free texture memory
	free(data);							 // Free game data memory
}