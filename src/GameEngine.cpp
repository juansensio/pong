#include "raylib.h"

#include "GameEngine.h"

void GameEngine::init() {
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(1270, 720, "pong");
    SetTargetFPS(3);               
}

void GameEngine::run() {
	init();
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	float x = 20;
	float v = 200; // px/s
	int frame = 0;
	float lastTime = GetTime();
    while (!WindowShouldClose())   
    {
        BeginDrawing();
        ClearBackground(BLACK);
		float currentTime = GetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		x += v * deltaTime;
		if (x > screenWidth - 30) v = 0;
		frame += 1;
        DrawCircle(x, screenHeight/2, 10, WHITE);
		DrawText(TextFormat("Frame %d", frame), 10, 10, 20, WHITE);
        DrawFPS(10, 40);
        EndDrawing();
    }
    CloseWindow();                  
}