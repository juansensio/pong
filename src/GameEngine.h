#pragma once

#include "raylib.h"
#include "raygui.h"
#include "raymath.h"
#include <map>

#include "Assets.h"
#include "scenes/Scenes.h"

using SceneMap = std::map<SceneType, Scene*>;

class GameEngine {
private:
    // Private constructor for singleton
    GameEngine();
    
    SceneMap         _scenes;
    SceneType        _current_scene;
    Assets           _assets;
    bool             _should_quit = false;

public:
    // Static method to get the singleton instance
    static GameEngine& instance() {
        static GameEngine instance;
        return instance;
    }

    ~GameEngine();

    void init();
    void run();
    void inputs();

    // std::shared_ptr<Scene> getCurrentScene() const { return _scenes.at(_current_scene); }
    Scene& getCurrentScene() { return *_scenes.at(_current_scene); }
    Assets& getAssets() { return _assets; }
    
    template<typename T> 
    void changeScene(const SceneType& sceneType) {
        // creamos siempre nueva escena, pero podríamos reutilizarla si ya existe
        // _scenes[sceneType] = std::make_shared<T>(*this);
        _scenes[sceneType] = new T(*this);
        _scenes[sceneType]->init();
        _current_scene = sceneType;
    }
    void quit() { _should_quit = true; }
    bool shouldQuit() const { return _should_quit; }
};
