#include "raylib.h"

#include "GameEngine.h"

void GameEngine::init() {
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(1270, 720, "pong");
    SetTargetFPS(10);               
}

void GameEngine::run() {
	init();
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	float x = 20;
	float v = 10;
	int frame = 0;
    while (!WindowShouldClose())   
    {
        BeginDrawing();
        ClearBackground(BLACK);
		x += v;
		if (x > screenWidth - 30) v = 0;
		frame += 1;
        DrawCircle(x, screenHeight/2, 10, WHITE);
		DrawText(TextFormat("Frame %d", frame), 10, 10, 20, WHITE);
        DrawFPS(10, 40);
        EndDrawing();
    }
    CloseWindow();                  
}