#pragma once

#include "Scene.h"
#include "objects/Objects.h"

class ScenePlay : public Scene
{
	Ball 	_ball;
	Wall 	_wall;
	
public:
	ScenePlay(GameEngine& game_engine) : Scene(game_engine) {}
	~ScenePlay() = default;

	void init() override;
	void update(const float& elapsed) override;
	void movement(const float& dt);
	void render() override;
	void doAction(const Action& action) override;
};
