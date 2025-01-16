#include "GameEngine.h"

void GameEngine::init() {
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(1270, 720, "pong");
    SetTargetFPS(60);               
}

void GameEngine::run() {
	init();
	changeScene<SceneLoading>("loading");
	int frame = 0;
	float lastTime = GetTime();
	float lag = 0.0f;
	float SECONDS_PER_UPDATE = 1.0f / 30.0f; // fps
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
			getCurrentScene()->update(SECONDS_PER_UPDATE);
			lag -= SECONDS_PER_UPDATE;
			updates++;
		}
		if (updates == 0 && lag > 0.0f) {
			getCurrentScene()->update(lag);
			lag = 0.0f;
			updates++;
		}
		frame += 1;
		getCurrentScene()->render();
		// DrawText(TextFormat("Frame %d", frame), 10, 10, 20, WHITE);
        DrawFPS(10, 10);
        // DrawText(TextFormat("Updates %d", updates), 10, 60, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();                  
}