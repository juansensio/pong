#include "GameEngine.h"

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {
	for (auto& scene : _scenes) {
		delete scene.second;
	}
}

void GameEngine::init() {
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
	InitWindow(1270, 720, "PONG");
    SetTargetFPS(60);               
}

void GameEngine::run() {
	init();
	// changeScene<SceneLoading>(SceneType::LOADING);
	changeScene<ScenePlay>(SceneType::PLAY);
	int frame = 0;
	float lastTime = GetTime();
	float lag = 0.0f;
	float SECONDS_PER_UPDATE = 1.0f / 60.0f; // fps
    while (!WindowShouldClose())   
    {
		inputs();
		BeginDrawing();
        ClearBackground(BLACK);
		float currentTime = GetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		lag += deltaTime;
		int updates = 0;
		while (lag >= SECONDS_PER_UPDATE) {
			getCurrentScene().update(SECONDS_PER_UPDATE);
			lag -= SECONDS_PER_UPDATE;
			updates++;
		}
		if (updates == 0 && lag > 0.0f) {
			getCurrentScene().update(lag);
			lag = 0.0f;
			updates++;
		}
		frame += 1;
<<<<<<< HEAD
		getCurrentScene()->render();
=======
		getCurrentScene().render();
		// DrawText(TextFormat("Frame %d", frame), 10, 10, 20, WHITE);
>>>>>>> actions
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();                  
}

void GameEngine::inputs() {
	for (auto& [key, action]: getCurrentScene().getActionMap())
	{
		if (IsKeyPressed(key) || IsKeyReleased(key)) {
			ActionType type = IsKeyPressed(key) ? ActionType::START : ActionType::END;
			Action action(getCurrentScene().getActionMap().at(key), type);
			getCurrentScene().doAction(action);
		}
	}
}