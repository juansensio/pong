#include "SceneMenu.h"
#include "../GameEngine.h"

void SceneMenu::init()
{
}

void SceneMenu::update(const float& elapsed)
{
}

void SceneMenu::render()
{
	const char *text = TextFormat("PLAY");
	int text_width = MeasureText(text, 20);
	// DrawText(text, GetScreenWidth() / 2 - text_width / 2, GetScreenHeight() / 2, 20, WHITE);
	if (GuiButton(Rectangle{(float)GetScreenWidth() / 2 - 50, (float)GetScreenHeight() / 2 - 25, 100, 50}, "PLAY")) {
		_game_engine.changeScene<ScenePlay>("play");
	}
}