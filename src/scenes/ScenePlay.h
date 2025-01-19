#pragma once

#include "Scene.h"

class ScenePlay : public Scene
{
	// game objects
	Player 					_player;
	Enemy 					_enemy;
	Ball 					_ball;
	std::vector<Wall> 		_walls;
	Goal 					_goal;
	Death 					_death;

	LevelManager 			_levelManager;

	// debug
	std::vector<float>       fpsBuffer;

public:
	ScenePlay(GameEngine& game_engine) : Scene(game_engine) {}
	~ScenePlay() = default;

	void init() override;
	void update(const float& elapsed) override;
	void movement(const float& dt);
	void collisions();
	void render() override;
	void doAction(const Action& action) override;

	void restart();
	void renderGUI();

	Player& getPlayer() override { return _player; }
	Ball& getBall() override { return _ball; }

	LevelManager& getLevelManager() { return _levelManager; }
};
