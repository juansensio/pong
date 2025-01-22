#include "ScenePlay.h"
#include "../GameEngine.h"

ScenePlay::ScenePlay(GameEngine& game_engine)
	: Scene(game_engine)
	, _ball(nullptr),
	_wall(nullptr) {}

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

	_wall = _entity_manager.addEntity(EntityType::WALL);
	_wall->add<CTransform>(Vector2{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, Vector2{0, 0});
	_wall->add<CRectShape>(20, 200, WHITE);
}

void ScenePlay::update(const float& dt)
{
	_entity_manager.update();
	
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	_ball->get<CTransform>().position.x += _ball->get<CTransform>().velocity.x * dt;
	// Colisión
	float playerX = _ball->get<CTransform>().position.x;
	float playerY = _ball->get<CTransform>().position.y;
	float wallX = _wall->get<CTransform>().position.x;
	float wallY = _wall->get<CTransform>().position.y;
	float wallWidth = _wall->get<CRectShape>().width;
	float wallHeight = _wall->get<CRectShape>().height;
	float playerRadius = _ball->get<CCircleShape>().radius;
	if (playerX >= wallX - wallWidth && playerX <= wallX - wallWidth + 10 &&
		playerY + playerRadius >= wallY - wallHeight/2 && playerY - playerRadius <= wallY + wallHeight/2) {
		_ball->destroy();
	}
}

void ScenePlay::render()
{
	for (auto& entity : _entity_manager.getEntities()) {
		Vector2 position = entity->get<CTransform>().position;
		if (entity->has<CCircleShape>()) {
			CCircleShape circle = entity->get<CCircleShape>();
			DrawCircle(position.x, position.y, circle.radius, circle.color);
		}
		if (entity->has<CRectShape>()) {
			CRectShape rect = entity->get<CRectShape>();
			DrawRectangle(position.x - rect.width/2, position.y - rect.height/2, rect.width, rect.height, rect.color);
		}
	}

	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 10, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>(SceneType::MENU);
	}

	// DEBUG
	DrawText(TextFormat("Entities: %d", _entity_manager.getEntities().size()), 10, 30, 20, RED);
}