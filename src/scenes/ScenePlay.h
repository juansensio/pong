#pragma once

#include "Scene.h"

class ScenePlay : public Scene
{
	Entity* _ball = nullptr;

public:
	ScenePlay(GameEngine& game_engine);
	~ScenePlay();

	void init() override;
	void update(const float& elapsed) override;
	void render() override;
};