#include "SceneMenu.h"
#include "../GameEngine.h"

SceneMenu::SceneMenu(GameEngine& game_engine)
	: Scene(game_engine) {}

SceneMenu::~SceneMenu() {}

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
	if (GuiButton(Rectangle{(float)GetScreenWidth() / 2 - 50, (float)GetScreenHeight() / 2 - 25, 100, 50}, "PLAY")) {
		_game_engine.changeScene<ScenePlay>(SceneType::PLAY);
	}
}