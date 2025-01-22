#pragma once

#include "Scene.h"

class SceneMenu : public Scene
{


public:
	SceneMenu(GameEngine& game_engine);
	~SceneMenu();

	void init() override;
	void update(const float& elapsed) override;
	void render() override;
};