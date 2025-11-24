#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/game.h"

// Specific include for web build
#if defined(WEB_BUILD)
#include <emscripten/emscripten.h>
#endif

// Function to wrap main gameloop
void GameLoop(GameData *gameData);

int main()
{
    // Create and initialize Game Data
    GameData gameData;
    InitGame(&gameData);

    // Web-specific loop configuration
#if defined(WEB_BUILD)
    emscripten_set_main_loop_arg((void (*)(void *))GameLoop, &gameData, 0, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        GameLoop(&gameData);
    }
#endif

    // Cleanup
    ExitGame(&gameData);

    return 0;
}

void GameLoop(GameData *gameData)
{
    UpdateGame(gameData);
    DrawGame(gameData);
}
