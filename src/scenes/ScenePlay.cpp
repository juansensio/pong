#include "ScenePlay.h"
#include "../GameEngine.h"

void ScenePlay::init()
{
	x = 20;
	v = 300; // px/s
}

void ScenePlay::update(const float& dt)
{
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	x += v * dt;
	if (x > screenWidth - 30) v = 0;
	// Colisión
	if (x >= screenWidth/2 - 50 && x <= screenWidth/2 - 40 && 
		screenHeight/2 - 10 <= screenHeight/2 + 50 && screenHeight/2 + 10 >= screenHeight/2 - 50) {
		x = screenWidth/2 - 60;
		v = 0;
	}
}

void ScenePlay::render()
{
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	DrawCircle(x, screenHeight/2, 10, WHITE);
	DrawRectangle(screenWidth/2 - 50, screenHeight/2 - 50, 10, 100, WHITE);
	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 10, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>("menu");
	}
}