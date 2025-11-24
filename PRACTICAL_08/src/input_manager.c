#include <raylib.h>

#include "../include/input_manager.h"

// Sample input initialization
void init_input_manager()
{
    // Initialize input sources (keyboard, controller, etc.)
}

// Sample input polling
Command poll_input()
{
    // Check keyboard input

    Command command = NONE;
    
    if (IsKeyDown(KEY_W))
        command |= MOVE_UP;
    if (IsKeyDown(KEY_S))
        command |= MOVE_DOWN;
    if (IsKeyDown(KEY_A))
        command |= MOVE_LEFT;
    if (IsKeyDown(KEY_D))
        command |= MOVE_RIGHT;
    if (IsKeyPressed(KEY_SPACE))
        command |= JUMP;
    if (IsKeyDown(KEY_F))
        command |= FIRE;

    TraceLog(LOG_INFO, "Keyboard Command %d", command);

    // Controller Input
    if (IsGamepadAvailable(0))
    {
        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP))
            command |= MOVE_UP;
        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
            command |= MOVE_DOWN;
        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
            command |= MOVE_LEFT;
        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
            command |= MOVE_RIGHT;

        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
            command |= JUMP;
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_TRIGGER) > 0.5f)
            command |= FIRE;

        TraceLog(LOG_INFO, "Controller Command %d", command);
    }

    return command;
}

void exit_input_manager()
{
    // Cleanup resources if needed
}
