#pragma once

#include "raylib.h"
#include "raygui.h"
#include "raymath.h"
#ifdef _DEBUG    
    #include "imgui.h"
    #include "rlImGui.h"
#endif
#include <map>
#include <iostream>

#include "Assets.h"
#include "scenes/Scenes.h"

using SceneMap = std::map<std::string, std::shared_ptr<Scene>>;

class GameEngine {
private:
    // Private constructor for singleton
    GameEngine() = default;
    
    SceneMap         _scenes;
    std::string      _current_scene;
    Assets           _assets;
    bool             _should_quit = false;

public:
    // Static method to get the singleton instance
    static GameEngine& instance() {
        static GameEngine instance;
        return instance;
    }

    void init();
    void run();
    void inputs();

    std::shared_ptr<Scene> getCurrentScene() const { return _scenes.at(_current_scene); }
    Assets& getAssets() { return _assets; }
    template<typename T> 
    void changeScene(const std::string& name) {
        _scenes[name] = std::make_shared<T>(*this);
        _scenes[name]->init();
        _current_scene = name;
    }
    void quit() { _should_quit = true; }
    bool shouldQuit() const { return _should_quit; }
};
