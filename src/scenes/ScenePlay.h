#pragma once

#include "Scene.h"
#include "objects/Objects.h"

class ScenePlay : public Scene
{
	// game objects

	Player 				_player;
	Enemy 				_enemy;
	Ball 				_ball;
	std::vector<Wall> 	_walls;
	Goal 				_goal;
	Death 				_death;
	
public:
	ScenePlay(GameEngine& game_engine);
	~ScenePlay();

	void init() override;
	void update(const float& elapsed) override;
	void movement(const float& dt);
	void collisions();
	void render() override;
	void doAction(const Action& action) override;
};
