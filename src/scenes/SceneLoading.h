#pragma once

#include "Scene.h"
#include "../GameEngine.h"

class SceneLoading : public Scene
{
	float 		_elapsedTime = 0.0f;
	Texture2D 	_texture;

public:
	SceneLoading(GameEngine& game_engine);
	~SceneLoading();

	void init() override;
	void update(const float& elapsed) override;
	void render() override;

};