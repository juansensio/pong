#include "SceneCredits.h"
#include "../GameEngine.h"

void SceneCredits::init()
{
}

void SceneCredits::update(const float& elapsed)
{
}

void SceneCredits::render()
{

	const char *text     = "This is an experimental game by Janus Noise";
	int        text_width = MeasureText(text, 20);

	DrawText(text,
	         (float)GetScreenWidth() / 2 - text_width / 2,
	         (float)GetScreenHeight() / 2 - 25,
	         20,
	         WHITE);

	if (GuiButton(Rectangle{(float)GetScreenWidth() / 2 - 50,
	                       (float)GetScreenHeight() / 2 + 25,
	                       100,
	                       50},
	              "MENU")) {
		_game_engine.changeScene<SceneMenu>("menu");
	}

	
}


void SceneCredits::doAction(const Action& action)
{
}