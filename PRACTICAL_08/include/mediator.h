#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <stdbool.h>

#include "command.h"
#include "player.h"

// Define the Mediator structure
typedef struct Mediator
{
    Player *player;
} Mediator;

// Function to create a mediator instance
Mediator *CreateMediator(Player *player);

// Handle Command
void MediatorHandleCommand(Mediator *mediator, Command command, float deltaTime);

#endif
