#pragma once

#include <memory>
#include <vector>

// Forward declare GameEngine to break circular dependency
class GameEngine;


class Scene
{
protected:
	GameEngine& _game_engine;

	// TODO: entities, actions, ...

public:
	Scene(GameEngine& game_engine) : _game_engine(game_engine) {}
	virtual ~Scene() {}

	virtual void init() = 0;
	virtual void update(const float& elapsed) = 0;
	virtual void render() = 0;
};