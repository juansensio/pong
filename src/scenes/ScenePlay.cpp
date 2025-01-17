#include "ScenePlay.h"
#include "../GameEngine.h"

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_player = _entity_manager.addEntity(EntityType::PLAYER);
	_player->x = 20;
	_player->v = 300; // px/s
}

void ScenePlay::update(const float& dt)
{
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	_player->x += _player->v * dt;
	if (_player->x > screenWidth - 30) _player->v = 0;
	// Colisión
	if (_player->x >= screenWidth/2 - 50 && _player->x <= screenWidth/2 - 40 && 
		screenHeight/2 - 10 <= screenHeight/2 + 50 && screenHeight/2 + 10 >= screenHeight/2 - 50) {
		_player->destroy();
	}
}

void ScenePlay::render()
{
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	if (_player->isAlive()) {
		DrawCircle(_player->x, screenHeight/2, 10, WHITE);
	}
	DrawRectangle(screenWidth/2 - 50, screenHeight/2 - 50, 10, 100, WHITE);
	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 10, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>("menu");
	}
}