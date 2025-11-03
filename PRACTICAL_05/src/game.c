#include "raylib.h"
#include "stdio.h"
#include "../include/game.h"

void InitGame() {
    printf("Game Initialized!\n");
}

void UpdateGame() {
    DrawText("Game Updating...", 190, 260, 20, DARKBLUE);
}

void DrawGame() {
    DrawText("Hello, Raylib Starter Kit!", 190, 180, 20, DARKBLUE);
    DrawCircle(410,120,110,RED);
    DrawRectangle(260,310,50,90,RED);
    DrawTriangle((Vector2){410,200},(Vector2){290,330},(Vector2){530,330}, GREEN);
    DrawTriangle((Vector2){410,330},(Vector2){280,475},(Vector2){540,475}, GREEN);
    DrawRectangle(500,450,60,80, RED);
    DrawRectangle(260,310,50,90,RED);
    DrawTriangle((Vector2){410,475},(Vector2){325,590},(Vector2){490,590},DARKBROWN);
    DrawCircle(410,120,110,(Color){253,240,0,255});
    DrawLineEx((Vector2){300,120},(Vector2){520,120},5,BLACK);
}

void CloseGame() {
    printf("Game Closed!\n");
}
