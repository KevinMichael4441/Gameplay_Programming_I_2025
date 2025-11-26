#include <stdbool.h>
#include <stdlib.h>

#include "mediator.h"
#include "player.h"
#include "command.h"

// For a good explanation on Mediator Pattern see
// https://www.geeksforgeeks.org/mediator-design-pattern/

// Creates and initializes a new mediator instance
Mediator *CreateMediator(Player *player)
{
    Mediator *mediator = (Mediator *)malloc(sizeof(Mediator));
    mediator->player = player;
    return mediator;
}

// Function to handle command and Execute via Command System
void MediatorHandleCommand(Mediator *mediator, Command command, float deltaTime)
{
    // Mediator delegates execution to Command
    // Command knows how to execute commands on player
    ExecuteCommand(command, mediator->player, deltaTime);
}