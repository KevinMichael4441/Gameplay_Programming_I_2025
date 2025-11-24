#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "mediator.h"

typedef struct {
    Player player;
    Mediator* mediator;
} GameData;

void InitGame(GameData* gameData);
void UpdateGame(GameData* gameData);
void DrawGame(GameData* gameData);
void ExitGame(GameData* gameData);

#endif // GAME_H
