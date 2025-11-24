#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "command.h"

void init_input_manager();
Command poll_input();
void exit_input_manager();

#endif // INPUT_MANAGER_H