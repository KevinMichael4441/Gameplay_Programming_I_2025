#include <raylib.h>

#include <stdio.h>
#include <math.h>

#include "player.h"

PlayerState *CreatePlayerState(Player *t_player)
{
	PlayerState *playerState = (PlayerState *)malloc(sizeof(PlayerState));
    playerState->color = t_player->color;
	playerState->x = t_player->x;
	playerState->y = t_player->y;
	playerState->health = t_player->health;

    return playerState;
}

Memento *CreateMemento(PlayerState *t_playerState)
{
	Memento *memento = (Memento *)malloc(sizeof(Memento));
    memento->playerState = t_playerState;
    return memento;
}

PlayerState* getState(Memento *t_memento)
{
	return t_memento->playerState;
}


// Keep player in screen bounds
void ClampPlayerOnScreen(Player *player)
{
	if (player->x < player->r)
		player->x = player->r;
	if (player->x > SCREEN_WIDTH - player->r)
		player->x = SCREEN_WIDTH - player->r;
	if (player->y < player->r)
		player->y = player->r;
	if (player->y > SCREEN_HEIGHT - player->r)
		player->y = SCREEN_HEIGHT - player->r;
}

// Player Idle Behaviour
void Idle(Player *player, float deltaTime)
{
	//saveState(player);
	// Simple breathing effect by changing radius over time
	// Idle animation
	player->breathTimer += deltaTime;
	player->color = GREEN; // Change color to indicate idle or default color
	float wave = sinf(player->breathTimer * 3.0f);
	float scale = 1.0f + (wave * 0.05f);

	player->r = (int)(DEFAULT_PLAYER_RADIUS * scale);
}

void saveState(Player *t_player)
{
	PlayerState *currentState = CreatePlayerState(t_player);
	t_player->memento = CreateMemento(currentState);
	t_player->undoMemento = NULL;
}

// Move player up
void MoveUp(Player *player)
{
	saveState(player);
	// Simple move up
	player->y -= 1;
	player->color = GREEN; // Change color to default color
	ClampPlayerOnScreen(player);
	printf("Player moved up to (%d, %d)\n", player->x, player->y);
}

// Move up and Fire
void MoveUpFire(Player *player)
{
	saveState(player);
	// Move up and fire
	player->y -= 1;
	player->x -= 3; // Recoil effect
	player->color = RED; // Change color to indicate firing
	ClampPlayerOnScreen(player);
	printf("\n\nPlayer moved up to (%d, %d) and FIRED\n\n", player->x, player->y);
}

// Move player down
void MoveDown(Player *player)
{
	saveState(player);
	// Simple move down
	player->y += 1;
	player->color = GREEN; // Change color to default color
	ClampPlayerOnScreen(player);
	printf("Player moved down to (%d, %d)\n", player->x, player->y);
}

// Move player left
void MoveLeft(Player *player)
{
	saveState(player);
	// Simple move left
	player->x -= 1;
	player->color = GREEN; // Change color to default color
	ClampPlayerOnScreen(player);
	printf("Player moved left to (%d, %d)\n", player->x, player->y);
}

// Move player right
void MoveRight(Player *player)
{
	saveState(player);
	// Simple move right
	player->x += 1;
	player->color = GREEN; // Change color to default color
	ClampPlayerOnScreen(player);
	printf("Player moved right to (%d, %d)\n", player->x, player->y);
}

// Player fires
void Fire(Player *player)
{
	saveState(player);
	// Simple Recoil effect
	player->x -= 3;
	player->color = RED; // Change color to indicate firing
	ClampPlayerOnScreen(player);
	printf("Player fired at position (%d, %d)\n", player->x, player->y);
}

void Jump(Player *player)
{
	saveState(player);
	// Simple jump effect
	player->y -= 10;
	player->color = DARKGREEN; // Change color to indicate Jumping
	ClampPlayerOnScreen(player);
	printf("Player jumped at position (%d, %d)\n", player->x, player->y);
}

void JumpFire(Player *player)
{
	saveState(player);
	// Simple jump and fire effect
	player->y -= 10;
	player->x -= 3;
	player->color = RED; // Change color to indicate firing
	ClampPlayerOnScreen(player);
	printf("\n\nJumping and Firing\n\n");
}

void undoAction(Player *t_player)
{
	t_player->undoMemento = CreateMemento(t_player->playerState);
	t_player->playerState = getState(t_player->memento);
}

void redoAction(Player *t_player)
{
	saveState(t_player);
	if (t_player->undoMemento != NULL)
	{
		t_player->playerState = getState(t_player->undoMemento);
	}
}