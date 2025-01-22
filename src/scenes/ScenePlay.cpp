#include "ScenePlay.h"
#include "../GameEngine.h"

ScenePlay::ScenePlay(GameEngine& game_engine)
	: Scene(game_engine)
	, _ball(nullptr) {}

ScenePlay::~ScenePlay() 
{
	delete _ball;
}

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_ball = _entity_manager.addEntity(EntityType::BALL);
	_ball->add<CTransform>(Vector2{20, (float)GetScreenHeight()/2}, Vector2{300, 0});
	_ball->add<CCircleShape>(10, WHITE);
}

void ScenePlay::update(const float& dt)
{
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	_ball->get<CTransform>().position.x += _ball->get<CTransform>().velocity.x * dt;
	// Colisión
	float x = _ball->get<CTransform>().position.x;
	if (x >= screenWidth/2 - 50 && x <= screenWidth/2 - 40 && 
		screenHeight/2 - 10 <= screenHeight/2 + 50 && screenHeight/2 + 10 >= screenHeight/2 - 50) {
		_ball->destroy();
	}
}

void ScenePlay::render()
{
	if (_ball->isAlive()) {
		Vector2 position = _ball->get<CTransform>().position;
		CCircleShape circle = _ball->get<CCircleShape>();
		DrawCircle(position.x, position.y, circle.radius, circle.color);
	}
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	DrawRectangle(screenWidth/2 - 50, screenHeight/2 - 50, 10, 100, WHITE);
	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 10, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>(SceneType::MENU);
	}
}