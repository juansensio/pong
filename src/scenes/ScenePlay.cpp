#include "ScenePlay.h"
#include "../GameEngine.h"

#include <iostream>

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_player = Player(_entity_manager.addEntity(EntityType::PLAYER));
	_ball = Ball(_entity_manager.addEntity(EntityType::BALL), _player);
	_enemy = Enemy(_entity_manager.addEntity(EntityType::ENEMY), _ball);
	_walls = {
		Wall(_entity_manager.addEntity(EntityType::WALL)),
		Wall(_entity_manager.addEntity(EntityType::WALL)),
	};
	_goal = Goal(_entity_manager.addEntity(EntityType::GOAL));
	_death = Death(_entity_manager.addEntity(EntityType::DEATH));

	_player.init();
	_enemy.init();
	_ball.init();
	_walls[0].init(10);
	_walls[1].init(GetScreenHeight() - 10);
	_goal.init();
	_death.init();

	registerAction(KEY_UP, ActionName::UP);
	registerAction(KEY_DOWN, ActionName::DOWN);
	registerAction(KEY_SPACE, ActionName::SPACE);
	registerAction(KEY_ENTER, ActionName::ENTER);
}

void ScenePlay::update(const float& dt)
{
	_entity_manager.update(); 
	_player.update(dt);
	if (_player.getLives() <= 0) {
		_game_engine.changeScene<SceneMenu>("menu");
	}
	_ball.update(dt);
	_enemy.update(dt);
	movement(dt);
	collisions();
}

void ScenePlay::movement(const float& dt) {
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CTransform>()) {
			auto velocity = Vector2Scale(entity->get<CTransform>().velocity, dt);
			entity->get<CTransform>().position = Vector2Add(
				entity->get<CTransform>().position,
				velocity
			);
			if (entity->has<CBoundingBox>()) {
				entity->get<CBoundingBox>().rect.x += velocity.x;
				entity->get<CBoundingBox>().rect.y += velocity.y;
			}
		}
	}
}

void ScenePlay::collisions() {
	CBoundingBox bb = _ball.getEntity()->get<CBoundingBox>();
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CBoundingBox>() && entity->id() != _ball.getEntity()->id()) {
			CBoundingBox bb2 = entity->get<CBoundingBox>();
			if (CheckCollisionRecs(bb.rect, bb2.rect)) {
				// TODO: compute overlap and move ball back
				_ball.collision(entity);
			}
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

	DrawText(TextFormat("Lives: %d", _player.getLives()), GetScreenWidth()/2 - 50, 20, 20, WHITE);
	DrawText(TextFormat("Score: %d", _player.getScore()), GetScreenWidth()/2 - 50, 40, 20, WHITE);

	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 10, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>("menu");
	}

	// DEBUG: render bounding boxes
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CBoundingBox>()) {
			CBoundingBox bounding_box = entity->get<CBoundingBox>();
			DrawRectangleLines(bounding_box.rect.x, bounding_box.rect.y, bounding_box.rect.width, bounding_box.rect.height, RED);
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
			_game_engine.changeScene<SceneMenu>("menu");
		}
	}
	else if (action.getType() == ActionType::END) {
		if (action.getName() == ActionName::UP) {
			_player.stopUp();
		}
		else if (action.getName() == ActionName::DOWN) {
			_player.stopDown();
		}
		else if (action.getName() == ActionName::SPACE) {
			_ball.init();
		}
	}
}
