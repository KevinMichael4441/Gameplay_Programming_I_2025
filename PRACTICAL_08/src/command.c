#include "../include/command.h"
#include "../include/mediator.h"

// Function to execute a command
void execute_command(Command command, Mediator* mediator) {

    // Delegate the command execution to the mediator
    mediator_execute_command(mediator, command);
    
}
