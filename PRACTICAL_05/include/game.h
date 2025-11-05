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

void CloseGame();


Texture2D m_texture, idle, walkA, walkB;
Vector2 m_direction, m_position;
int m_velocity;

int m_currentWalk = 0;
int m_walkDelay = 15;
int m_walkTimer = 0;



#endif // GAME_H