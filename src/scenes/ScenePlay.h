#pragma once

#include "Scene.h"
#include "objects/Objects.h"

class ScenePlay : public Scene
{
	Ball _ball;
	Wall _wall;

public:
	ScenePlay(GameEngine& game_engine);
	~ScenePlay();

	void init() override;
	void update(const float& elapsed) override;
	void render() override;
	void movement(const float& dt);
};
