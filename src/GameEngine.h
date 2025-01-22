#pragma once

#include "raylib.h"
#include "raygui.h"
#include "raymath.h"
#include <map>

#include "scenes/Scenes.h"

enum SceneType {
	LOADING = 0,
	MENU = 1,
	PLAY = 2
};

using SceneMap = std::map<SceneType, Scene*>;

class GameEngine {
    SceneMap         _scenes;
    SceneType        _current_scene;

    // TODO: config, assets, ...

public:
    GameEngine();
    ~GameEngine();

    void init();
    void run();
    void inputs();

    Scene& getCurrentScene() { return *_scenes.at(_current_scene); }
    
    template<typename T> 
    void changeScene(const SceneType& sceneType) {
        // creamos siempre nueva escena, pero podríamos reutilizarla si ya existe
        // _scenes[sceneType] = std::make_shared<T>(*this);
        _scenes[sceneType] = new T(*this);
        _scenes[sceneType]->init();
        _current_scene = sceneType;
    }
};
