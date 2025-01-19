#pragma once

#include "Scene.h"
#include "Level.h"

class ScenePlay : public Scene
{
	// game objects

	Player 					_player;
	Enemy 					_enemy;
	Ball 					_ball;
	std::vector<Wall> 		_walls;
	Goal 					_goal;
	Death 					_death;

	std::vector<Level> 		_levels;
	int 					_currentLevel;
	int 					_numLevels;

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

	const Level& getLevel() const override { return _levels[_currentLevel]; }
	void loadNextLevel() override;

	const Player& getPlayer() const override { return _player; }
	const Ball& getBall() const override { return _ball; }
};
