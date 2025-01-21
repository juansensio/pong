#pragma once

#include "Scene.h"
#include "ResultsManager.h"

class SceneResults : public Scene
{
	ResultsManager _resultsManager;	
	
public:
	SceneResults(GameEngine& game_engine) : Scene(game_engine) {}
	~SceneResults() = default;

	void init() override;
	void update(const float& elapsed) override;
	void render() override;
	void doAction(const Action& action) override;
};
