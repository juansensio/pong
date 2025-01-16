#pragma once

#include "raylib.h"
#include <map>
#include "raygui.h"
#include "scenes/Scenes.h"

using SceneMap = std::map<std::string, std::shared_ptr<Scene>>;

class GameEngine {
    SceneMap         _scenes;
    std::string     _current_scene;

    // TODO: config, assets, ...

public:
    GameEngine() = default;

    void init();
    void run();

    std::shared_ptr<Scene> getCurrentScene() const { return _scenes.at(_current_scene); }
    
    template<typename T> 
    void changeScene(const std::string& name) {
        _scenes[name] = std::make_shared<T>(*this);
        _current_scene = name;
        _scenes[name]->init();
    }
};
