#include "raylib.h"

#include "GameEngine.h"

void GameEngine::init() {
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(1270, 720, "pong");
    SetTargetFPS(120);               
}

void GameEngine::run() {
	init();
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	float x = 20;
	float v = 300; // px/s
	int frame = 0;
	float lastTime = GetTime();
	float lag = 0.0f;
	float SECONDS_PER_UPDATE = 1.0f / 60.0f; // fps
    while (!WindowShouldClose())   
    {
        BeginDrawing();
        ClearBackground(BLACK);
		float currentTime = GetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		lag += deltaTime;
		int updates = 0;
		while (lag >= SECONDS_PER_UPDATE) {
			x += v * SECONDS_PER_UPDATE;
			if (x > screenWidth - 30) v = 0;
			// Colisión
			if (x >= screenWidth/2 - 50 && x <= screenWidth/2 - 40 && 
				screenHeight/2 - 10 <= screenHeight/2 + 50 && screenHeight/2 + 10 >= screenHeight/2 - 50) {
				x = screenWidth/2 - 60;
				v = 0;
			}
			lag -= SECONDS_PER_UPDATE;
			updates++;
		}
		frame += 1;
		DrawCircle(x, screenHeight/2, 10, WHITE);
		DrawRectangle(screenWidth/2 - 50, screenHeight/2 - 50, 10, 100, WHITE);
		DrawText(TextFormat("Frame %d", frame), 10, 10, 20, WHITE);
        DrawFPS(10, 40);
        DrawText(TextFormat("Updates %d", updates), 10, 60, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();                  
}