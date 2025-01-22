#pragma once

#include "raylib.h"
#include "raygui.h"
#include <map>

#include "scenes/Scenes.h"


using SceneMap = std::map<std::string, Scene*>;

class GameEngine {
    SceneMap         _scenes;
    std::string      _current_scene;

    // TODO: config, assets, ...

public:
    GameEngine();
    ~GameEngine();

    void init();
    void run();

    Scene& getCurrentScene() { return *_scenes.at(_current_scene); }
    
    template<typename T> 
    void changeScene(const std::string& name) {
        // creamos siempre nueva escena, pero podríamos reutilizarla si ya existe
        // _scenes[name] = std::make_shared<T>(*this);
        _scenes[name] = new T(*this);
        _scenes[name]->init();
        _current_scene = name;
    }
};
