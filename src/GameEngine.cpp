#include "GameEngine.h"

void GameEngine::init() {
	// Try development path (./assets) first on all platforms
	if (DirectoryExists("assets")) {
		// We're in development mode, assets directory is in current path
		TraceLog(LOG_INFO, "Using development assets path");
	} else {
		#if defined(__APPLE__)
			// macOS .app bundle case
			const char* basePath = GetApplicationDirectory();
			if (basePath != nullptr) {
				std::string resourcePath = std::string(basePath) + "/../Resources";
				ChangeDirectory(resourcePath.c_str());
				TraceLog(LOG_INFO, "Using production assets path: %s", resourcePath.c_str());
			} else {
				TraceLog(LOG_ERROR, "Failed to find assets directory");
			}
		#elif defined(_WIN32)
			// Windows exe case - assets should be next to executable
			const char* basePath = GetApplicationDirectory();
			if (basePath != nullptr) {
				ChangeDirectory(basePath);
				TraceLog(LOG_INFO, "Using production assets path: %s", basePath);
			} else {
				TraceLog(LOG_ERROR, "Failed to find assets directory");
			}
		#endif
	}
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(1270, 720, "pong");
	InitAudioDevice();
    SetTargetFPS(60);               
}

void GameEngine::run() {
	init();
	_assets.load();
	changeScene<SceneLoading>("loading");
	// changeScene<ScenePlay>("play");
	int frame = 0;
	float lastTime = GetTime();
	float lag = 0.0f;
	float SECONDS_PER_UPDATE = 1.0f / 60.0f; // fps
    while (!WindowShouldClose() && !_should_quit)   
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
        EndDrawing();
    }
    CloseWindow();                  
}

void GameEngine::inputs() {
	for (auto& [key, action]: getCurrentScene()->getActionMap())
	{
		if (IsKeyPressed(key) || IsKeyReleased(key)) {
			ActionType type = IsKeyPressed(key) ? ActionType::START : ActionType::END;
			Action action(getCurrentScene()->getActionMap().at(key), type);
			getCurrentScene()->doAction(action);
		}
	}
}