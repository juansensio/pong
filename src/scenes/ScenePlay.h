#pragma once

#include "Scene.h"
#include "objects/Objects.h"

class ScenePlay : public Scene
{
	Player 	_player;
	Wall 	_wall;
	
public:
	ScenePlay(GameEngine& game_engine) : Scene(game_engine) {}
	~ScenePlay() = default;

	void init() override;
	void update(const float& elapsed) override;
	void render() override;
};