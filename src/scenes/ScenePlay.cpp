#include "ScenePlay.h"
#include "../GameEngine.h"

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_player = _entity_manager.addEntity(EntityType::PLAYER);
	_player->add<CTransform>(Vector2{20, (float)GetScreenHeight()/2}, Vector2{300, 0});
	_player->add<CCircleShape>(10, WHITE);
}

void ScenePlay::update(const float& dt)
{
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	_player->get<CTransform>().position.x += _player->get<CTransform>().velocity.x * dt;
	// Colisión
	float x = _player->get<CTransform>().position.x;
	if (x >= screenWidth/2 - 50 && x <= screenWidth/2 - 40 && 
		screenHeight/2 - 10 <= screenHeight/2 + 50 && screenHeight/2 + 10 >= screenHeight/2 - 50) {
		_player->destroy();
	}
}

void ScenePlay::render()
{
	if (_player->isAlive()) {
		Vector2 position = _player->get<CTransform>().position;
		CCircleShape circle = _player->get<CCircleShape>();
		DrawCircle(position.x, position.y, circle.radius, circle.color);
	}
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	DrawRectangle(screenWidth/2 - 50, screenHeight/2 - 50, 10, 100, WHITE);
	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 10, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>("menu");
	}
}