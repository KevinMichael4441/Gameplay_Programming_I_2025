#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <stdbool.h>

#include "command.h"
#include "player.h"

// Define the Mediator structure
typedef struct Mediator {
    Player* player;
} Mediator;

// Function to create a mediator instance
Mediator* create_mediator(Player* player);

// Execute Command
void mediator_execute_command(Mediator* mediator, Command command);

#endif

