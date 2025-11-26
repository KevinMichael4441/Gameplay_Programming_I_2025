#include "command.h"
#include "mediator.h"

// Function to execute a command
void ExecuteCommand(Command command, Player *player, float deltaTime)
{
    // Handle idle (input NONE)
    if (command == NONE)
    {
        Idle(player, deltaTime);
        return; // Nothing to process
    }
    else if (command == UNDO)
    {
        undoAction(player);
        return;
    }
    else if (command == REDO)
    {
        redoAction(player);
        return;
    }

    // Handle basic movement
    // MOVE DOWN, LEFT, RIGHT are single commands (no combos)
    // Handle them directly
    if (IsCommandActive(command, MOVE_DOWN))
        MoveDown(player);

    if (IsCommandActive(command, MOVE_LEFT))
        MoveLeft(player);

    if (IsCommandActive(command, MOVE_RIGHT))
        MoveRight(player);

    // Handle combined commands (combos)
    // Combined MOVE UP AND FIRE
    if (IsCommandActive(command, MOVE_UP) && IsCommandActive(command, FIRE))
    {
        MoveUpFire(player);
    }

    // Combined JUMP AND FIRE (if not MOVE_UP & FIRE)
    else if (IsCommandActive(command, JUMP) && IsCommandActive(command, FIRE))
    {
        JumpFire(player);
    }
    
    // Handle individual commands such as MOVE UP, JUMP, FIRE after combos
    else
    {
        if (IsCommandActive(command, MOVE_UP))
        {
            MoveUp(player);
        }
        if (IsCommandActive(command, JUMP))
        {
            Jump(player);
        }
        if (IsCommandActive(command, FIRE))
        {
            Fire(player);
        }
    }
}

// Check if a specific command is active
bool IsCommandActive(Command command, Command filter)
{
    return (command & filter) != 0;
}

// Get the binary representation of the command as a string
// The buffer should be at least COUNT + 1 in size to hold the "string" null terminator
// Example: For command = MOVE_UP | FIRE, the output will be "100001"
void GetCommandBits(Command command, char *buffer)
{
    for (int i = COUNT; i >= 0; i--)
    {
        buffer[COUNT - i] = (command & (1 << i)) ? '1' : '0';
    }
    buffer[COUNT] = '\0'; // null terminator
}