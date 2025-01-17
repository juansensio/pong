#pragma once

#include <memory>
#include <vector>

#include "entities/EntityManager.h"
#include "Actions.h"

// Forward declare GameEngine to break circular dependency
class GameEngine;

using ActionMap = std::map<int, ActionName>;

class Scene
{
protected:
	GameEngine& 				_game_engine;
	EntityManager 				_entity_manager;
	ActionMap					_action_map;

public:
	Scene(GameEngine& game_engine) : _game_engine(game_engine) {}
	virtual ~Scene() = default;

	virtual void init() = 0;
	virtual void update(const float& elapsed) = 0;
	virtual void render() = 0;
	virtual void doAction(const Action& action) = 0;

	void registerAction(int key, const ActionName& name) {_action_map[key] = name;}
	const ActionMap& getActionMap() const { return _action_map; }
};