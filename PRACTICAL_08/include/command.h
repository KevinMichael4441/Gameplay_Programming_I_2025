#ifndef COMMAND_H
#define COMMAND_H

// Forward declaration of the Mediator struct
typedef struct Mediator Mediator;

// Define the Command enum
typedef enum {
    NONE       = 0,
    MOVE_UP    = 1 << 0,
    MOVE_DOWN  = 1 << 1,
    MOVE_LEFT  = 1 << 2,
    MOVE_RIGHT = 1 << 3,
    JUMP       = 1 << 4,
    FIRE       = 1 << 5
} Command;

// Function to execute a command
void execute_command(Command command, Mediator* mediator);

#endif // COMMAND_H

