#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "constants.h"

// Player Structure Data
typedef struct
{
    int x;
    int y;
    int r;
    int health;
    float breathTimer;
    Color color;
} Player;

// Player Behaviours
void Idle(Player *player, float deltaTime);
void MoveUp(Player *player);
void MoveDown(Player *player);
void MoveLeft(Player *player);
void MoveRight(Player *player);

void Jump(Player *player);
void Fire(Player *player);

void JumpFire(Player *player);
void MoveUpFire(Player *player);

void ClampPlayerOnScreen(Player *player); // Player stays within screen bounds

#endif
