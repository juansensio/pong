#include "ScenePlay.h"
#include "../GameEngine.h"

ScenePlay::ScenePlay(GameEngine& game_engine) 
	: Scene(game_engine)
	, _player(nullptr)
	, _enemy(nullptr)
	, _ball(nullptr)
	, _walls({nullptr, nullptr})
	, _goal(nullptr)
	, _death(nullptr) {}

ScenePlay::~ScenePlay() {}

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_player = Player(_entity_manager.addEntity(EntityType::PLAYER));
	// _enemy = Enemy(_entity_manager.addEntity(EntityType::ENEMY));
	// _ball = Ball(_entity_manager.addEntity(EntityType::BALL));
	// _walls = {
	// 	Wall(_entity_manager.addEntity(EntityType::WALL)),
	// 	Wall(_entity_manager.addEntity(EntityType::WALL)),
	// };
	// _goal = Goal(_entity_manager.addEntity(EntityType::GOAL));
	// _death = Death(_entity_manager.addEntity(EntityType::DEATH));

	_player.init();
	// _enemy.init();
	// _ball.init();
	// for (auto& wall : _walls) {
	// 	wall.init();
	// }
	// _goal.init();
	// _death.init();

	registerAction(KEY_UP, ActionName::UP);
	registerAction(KEY_DOWN, ActionName::DOWN);
	registerAction(KEY_ENTER, ActionName::ENTER);
}

void ScenePlay::update(const float& dt)
{
	_player.update(dt);
	movement(dt);
	_entity_manager.update(); 
}

void ScenePlay::movement(const float& dt)
{
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CTransform>()) {
			auto& transform = entity->get<CTransform>();
			transform.prevPosition = transform.position;
			transform.position += transform.velocity * dt;
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

	// DEBUG: render bounding boxes
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CBoundingBox>()) {
			auto position = entity->get<CTransform>().position;
			CBoundingBox bb = entity->get<CBoundingBox>();
			DrawRectangleLines(position.x - bb.halfSize.x, position.y - bb.halfSize.y, bb.size.x, bb.size.y, RED);
		}
	}
}

void ScenePlay::doAction(const Action& action)
{
	if (action.getType() == ActionType::START) {
		if (action.getName() == ActionName::UP) {
			_player.moveUp();
		}
		else if (action.getName() == ActionName::DOWN) {
			_player.moveDown();
		}
		else if (action.getName() == ActionName::ENTER) {
			_game_engine.changeScene<SceneMenu>(SceneType::MENU);
		}
	}
	else if (action.getType() == ActionType::END) {
		if (action.getName() == ActionName::UP) {
			_player.stop();
		}
		else if (action.getName() == ActionName::DOWN) {
			_player.stop();
		}
	}
}