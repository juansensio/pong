#include "ScenePlay.h"
#include "../GameEngine.h"

ScenePlay::ScenePlay(GameEngine& game_engine)
	: Scene(game_engine)
	, _ball(nullptr)
	, _wall(nullptr) {}

ScenePlay::~ScenePlay() {}

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_ball = Ball(_entity_manager.addEntity(EntityType::BALL));
	_ball.init();
	
	_wall = Wall(_entity_manager.addEntity(EntityType::WALL));
	_wall.init();

	registerAction(KEY_UP, ActionName::UP);
	registerAction(KEY_DOWN, ActionName::DOWN);
}

void ScenePlay::update(const float& dt)
{
	_wall.update(dt);
	movement(dt);
	// Colisión
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	float playerX = _ball.position().x;
	float playerY = _ball.position().y;
	float wallX = _wall.position().x;
	float wallY = _wall.position().y;
	float wallWidth = _wall.getEntity().get<CRectShape>().width;
	float wallHeight = _wall.getEntity().get<CRectShape>().height;
	float playerRadius = _ball.getEntity().get<CCircleShape>().radius;
	if (playerX >= wallX - wallWidth && playerX <= wallX - wallWidth + 10 &&
		playerY + playerRadius >= wallY - wallHeight/2 && playerY - playerRadius <= wallY + wallHeight/2) {
		_ball.destroy();
	}
	_entity_manager.update(); // add and remove entities 
}

void ScenePlay::movement(const float& dt)
{
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CTransform>()) {
			CTransform transform = entity->get<CTransform>();
			transform.position += transform.velocity * dt;
			entity->get<CTransform>() = transform;
		}
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

#include <iostream>

void ScenePlay::doAction(const Action& action)
{
	if (action.getType() == ActionType::START) {
		if (action.getName() == ActionName::UP) {
			std::cout << "UP" << std::endl;
			_wall.moveUp();
		}
		else if (action.getName() == ActionName::DOWN) {
			_wall.moveDown();
		}
		else if (action.getName() == ActionName::ENTER) {
			_game_engine.changeScene<SceneMenu>(SceneType::MENU);
		}
	}
	else if (action.getType() == ActionType::END) {
		if (action.getName() == ActionName::UP) {
			_wall.stop();
		}
		else if (action.getName() == ActionName::DOWN) {
			_wall.stop();
		}
	}
}