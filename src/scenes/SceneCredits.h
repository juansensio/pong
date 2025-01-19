#pragma once

#include "Scene.h"

class SceneCredits : public Scene
{


public:
	SceneCredits(GameEngine& game_engine) : Scene(game_engine) {}
	~SceneCredits() = default;

	void init() override;
	void update(const float& elapsed) override;
	void render() override;
	void doAction(const Action& action) override;
};
