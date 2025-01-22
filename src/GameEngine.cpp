#include "raylib.h"

#include "GameEngine.h"

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {}

void GameEngine::init() {
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
	InitWindow(1270, 720, "PONG");
    SetTargetFPS(60);               
}

void GameEngine::run() {
	init();
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
    while (!WindowShouldClose())   
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Hola Mundo!", screenWidth/2 - MeasureText("Hola Mundo!", 20)/2, screenHeight/2 - 10, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();                  
}