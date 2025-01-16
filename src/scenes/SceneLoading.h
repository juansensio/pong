#pragma once

#include "Scene.h"

class SceneLoading : public Scene
{


public:
	SceneLoading(GameEngine& game_engine) : Scene(game_engine) {}
	~SceneLoading() = default;

	void init() override;
	void update(const float& elapsed) override;
	void render() override;

private:
	float _elapsedTime = 0.0f;
};