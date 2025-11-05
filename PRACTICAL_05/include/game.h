#ifndef GAME_H
#define GAME_H

#include "raymath.h"

void InitGame();

void UpdateGame();
void UpdatePlayer();
void MovePlayer();
void BoundaryChecking();

void DrawGame();
void DrawChristmasTree();
void DrawMessage();

void CloseGame();



#endif // GAME_H
