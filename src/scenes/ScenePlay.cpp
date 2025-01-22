#include "ScenePlay.h"
#include "../GameEngine.h"

ScenePlay::ScenePlay(GameEngine& game_engine)
	: Scene(game_engine)
	, _ball(nullptr) {}

ScenePlay::~ScenePlay() {}

void ScenePlay::init()
{
	_entity_manager = EntityManager();
	_ball = _entity_manager.addEntity(EntityType::BALL);
	_ball->x = 20;
	_ball->v = 300; // px/s
}

void ScenePlay::update(const float& dt)
{
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	_ball->x += _ball->v * dt;
	if (_ball->x > screenWidth - 30) _ball->v = 0;
	// Colisión
	if (_ball->x >= screenWidth/2 - 50 && _ball->x <= screenWidth/2 - 40 && 
		screenHeight/2 - 10 <= screenHeight/2 + 50 && screenHeight/2 + 10 >= screenHeight/2 - 50) {
		_ball->destroy();
	}
}

void ScenePlay::render()
{
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	if (_ball->isAlive()) {
		DrawCircle(_ball->x, screenHeight/2, 10, WHITE);
	}
	DrawRectangle(screenWidth/2 - 50, screenHeight/2 - 50, 10, 100, WHITE);
	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 10, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>(SceneType::MENU);
	}
}