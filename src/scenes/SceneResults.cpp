#include "SceneResults.h"
#include "../GameEngine.h"

void SceneResults::init()
{
	_resultsManager.loadScores();
}

void SceneResults::update(const float& elapsed)
{
}

void SceneResults::render()
{

	const int boxWidth = 200;
	const int boxHeight = 300; // Made taller to fit scores
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	Rectangle bounds = {
		(float)(screenWidth - boxWidth)/2,
		(float)(screenHeight - boxHeight)/2,
		(float)boxWidth,
		(float)boxHeight
	};

	// Draw scores
	const int scoreSpacing = 25;
	float scoreY = bounds.y + 20;
	
	const char* titleText = "YOUR BEST TIMES";
	float titleWidth = MeasureText(titleText, 20);
	DrawText(titleText, bounds.x + (bounds.width - titleWidth)/2, scoreY, 20, WHITE);
	scoreY += 40;

	for (const auto& score : _resultsManager.getScores()) {
		const char* scoreText = TextFormat("%.2f", score);
		float scoreWidth = MeasureText(scoreText, 20);
		DrawText(scoreText, bounds.x + (bounds.width - scoreWidth)/2, scoreY, 20, WHITE);
		scoreY += scoreSpacing;
	}

	// Calculate button dimensions
	const int buttonWidth = 120;
	const int buttonHeight = 40;
	const int buttonSpacing = 10;
	float buttonX = bounds.x + (bounds.width - buttonWidth)/2;
	float buttonY = bounds.y + boxHeight - (2 * buttonHeight + buttonSpacing + 20); // Position from bottom

	// Draw buttons centered in the group box
	if (GuiButton(Rectangle{buttonX, buttonY, buttonWidth, buttonHeight}, "PLAY")) {
		_game_engine.changeScene<ScenePlay>("play");
	}
	if (GuiButton(Rectangle{buttonX, buttonY + (buttonHeight + buttonSpacing), buttonWidth, buttonHeight}, "MENU")) {
		_game_engine.changeScene<SceneMenu>("menu");
	}
	
}


void SceneResults::doAction(const Action& action)
{
}