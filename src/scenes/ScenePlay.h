#pragma once

#include "Scene.h"
#include "entities/Objects.h"

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
	void doAction(const Action& action) override;
	void movement(const float& dt);
};
