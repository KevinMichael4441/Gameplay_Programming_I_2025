#include <stdbool.h>
#include <stdlib.h>
#include "../include/mediator.h"
#include "../include/player.h"
#include "../include/command.h"

// For a good explanation on Mediator Pattern see
// https://www.geeksforgeeks.org/mediator-design-pattern/

// Creates and initializes a new mediator instance
Mediator *create_mediator(Player *player)
{
    Mediator *mediator = (Mediator *)malloc(sizeof(Mediator));
    mediator->player = player;
    return mediator;
}

// Function to execute a command through the mediator
void mediator_execute_command(Mediator *mediator, Command command)
{
    // TODO: Consider cleaning up with function pointers
    if (command & MOVE_DOWN)
        player_move_down(mediator->player);
    if (command & MOVE_LEFT)
        player_move_left(mediator->player);
    if (command & MOVE_RIGHT)
        player_move_right(mediator->player);

    // Combined MOVE UP AND FIRE
    if ((command & MOVE_UP) && (command & FIRE))
    {
        player_move_up_fire(mediator->player);
        // SEND THE EVENT MOVE_UP_FIRE
    }

    // Combined JUMP AND FIRE (if ! MOVE_UP & FIRE)
    else if ((command & JUMP) && (command & FIRE))
    {
        player_jump_fire(mediator->player);
        // SEND THE EVENT JUMP_FIRE
    }

    // Handle others
    else
    {
        if (command & MOVE_UP)
        {
            player_move_up(mediator->player);
            // SEND THE EVENT MOVE_UP
        }
        if (command & JUMP)
        {
            player_jump(mediator->player);
            // SEND THE EVENT JUMP
        }
        if (command & FIRE)
        {
            player_fire(mediator->player);
            // SEND THE EVENT FIRE
        }
    }
}
