#ifndef AI_MANAGER_H
#define AI_MANAGER_H

#include "./command/command.h"
#include <raylib.h>
#include <raymath.h>

void InitAIManager();
Command PollAI();
Command getMoveCommand(Vector2 t_AICenter, Vector2 t_targetCenter);
void ExitInputManager();

#endif // AI_MANAGER_H