#pragma once

#include "Scene.h"

class ScenePlay : public Scene
{

	bool 					_paused = false;
	bool					_hud = true;
	float					_time = 0;

	// game objects

	Player 					_player;
	Enemy 					_enemy;
	Ball 					_ball;
	std::vector<Wall> 		_walls;
	Goal 					_goal;
	Death 					_death;
	Shop					_shop;

	LevelManager 			_levelManager;
	ResultsManager			_resultsManager;

	// debug
	std::vector<float>       fpsBuffer;

public:
	ScenePlay(GameEngine& game_engine);
	~ScenePlay();

	void init() override;
	void update(const float& elapsed) override;
	void movement(const float& dt);
	void collisions();
	void render() override;
	void doAction(const Action& action) override;

	void restart();
	void renderGUI();
	void pause() { _paused = true; }
	void resume() { _paused = false; }

	Player& getPlayer() override { return _player; }
	Ball& getBall() override { return _ball; }
	Enemy& getEnemy() override { return _enemy; }

	LevelManager& getLevelManager() { return _levelManager; }
};
