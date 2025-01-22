#pragma once

#include "Scene.h"

class ScenePlay : public Scene
{
	float x;
	float v; 

public:
	ScenePlay(GameEngine& game_engine);
	~ScenePlay();

	void init() override;
	void update(const float& elapsed) override;
	void render() override;
};