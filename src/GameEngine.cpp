#include "GameEngine.h"

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {
	for (auto& scene : _scenes) {
		delete scene.second;
	}
}

void GameEngine::init() {
	// en desarrollo, queremos usar el directorio assets en el directorio actual
	if (DirectoryExists("assets")) {
		TraceLog(LOG_INFO, "Using development assets path");
	} else {
		// en produccion, depende de la plataforma, buscaremos los assets donde toque
		#if defined(__APPLE__)
			// macOS .app bundle
			const char* basePath = GetApplicationDirectory();
			if (basePath != nullptr) {
				std::string resourcePath = std::string(basePath) + "/../Resources";
				ChangeDirectory(resourcePath.c_str());
				TraceLog(LOG_INFO, "Using production assets path: %s", resourcePath.c_str());
			} else {
				TraceLog(LOG_ERROR, "Failed to find assets directory");
			}
		#elif defined(_WIN32)
			// Windows exe case
			const char* basePath = GetApplicationDirectory();
			if (basePath != nullptr) {
				ChangeDirectory(basePath);
				TraceLog(LOG_INFO, "Using production assets path: %s", basePath);
			} else {
				TraceLog(LOG_ERROR, "Failed to find assets directory");
			}
		#endif
	}
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
	InitWindow(1270, 720, "PONG");
	InitAudioDevice();
    SetTargetFPS(60);    
	#ifdef _DEBUG
		rlImGuiSetup(true);
	#endif
       
}

void GameEngine::run() {
	init();
	_assets.load();
	#ifdef _DEBUG
		changeScene<ScenePlay>(SceneType::PLAY);
	#else
		changeScene<SceneLoading>(SceneType::LOADING);
	#endif
	int frame = 0;
	float lastTime = GetTime();
	float lag = 0.0f;
	float SECONDS_PER_UPDATE = 1.0f / 60.0f; // fps
    while (!WindowShouldClose() && !_should_quit)   
    {
		inputs();
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
		BeginDrawing();
        ClearBackground(BLACK);
		#ifdef _DEBUG
			rlImGuiBegin();
		#endif
		getCurrentScene().render();
		#ifdef _DEBUG
			rlImGuiEnd();
		#endif
        EndDrawing();
    }
	#ifdef _DEBUG
		rlImGuiShutdown();
	#endif
    CloseWindow();                  
}

void GameEngine::inputs() {
	for (auto& [key, action]: getCurrentScene().getActionMap())
	{
		if (IsMouseButtonPressed(key) || IsMouseButtonReleased(key)) {
			ActionType type = IsMouseButtonPressed(key) ? ActionType::START : ActionType::END;
			Action action(getCurrentScene().getActionMap().at(key), type);
			getCurrentScene().doAction(action);
		} else if (IsKeyPressed(key) || IsKeyReleased(key)) {
			ActionType type = IsKeyPressed(key) ? ActionType::START : ActionType::END;
			Action action(getCurrentScene().getActionMap().at(key), type);
			getCurrentScene().doAction(action);
		}
	}
}