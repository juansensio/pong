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
	float x = 20;
	float v = 300; // px/s
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
		// Colisión
		// if (x >= screenWidth/2 - 50 && x <= screenWidth/2 - 40 && 
		// 	screenHeight/2 - 10 <= screenHeight/2 + 50 && screenHeight/2 + 10 >= screenHeight/2 - 50) {
		// 	x = screenWidth/2 - 60;
		// 	v = 0;
		// }
		DrawCircle(x, screenHeight/2, 10, WHITE);
		// DrawRectangle(screenWidth/2 - 50, screenHeight/2 - 50, 10, 100, WHITE);
		DrawText(TextFormat("Frame %d", frame), 10, 10, 20, WHITE);
        DrawFPS(10, 40);
        EndDrawing();
    }
    CloseWindow();                  
}