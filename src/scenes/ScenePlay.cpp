#include "ScenePlay.h"
#include "../GameEngine.h"

#include <iostream>

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_player = Player(_entity_manager.addEntity(EntityType::PLAYER));
	_enemy = Enemy(_entity_manager.addEntity(EntityType::ENEMY));
	_ball = Ball(_entity_manager.addEntity(EntityType::BALL));
	_walls = {
		Wall(_entity_manager.addEntity(EntityType::WALL)),
		Wall(_entity_manager.addEntity(EntityType::WALL)),
	};
	// _goal = Goal(_entity_manager.addEntity(EntityType::GOAL));
	// _death = Death(_entity_manager.addEntity(EntityType::DEATH));

	_player.init();
	_enemy.init();
	_ball.init();
	_walls[0].init(10);
	_walls[1].init(GetScreenHeight() - 10);
	// _goal.init();
	// _death.init();

	registerAction(KEY_UP, ActionName::UP);
	registerAction(KEY_DOWN, ActionName::DOWN);
	registerAction(KEY_SPACE, ActionName::SPACE);
	registerAction(KEY_ENTER, ActionName::ENTER);
}

void ScenePlay::update(const float& dt)
{
	_entity_manager.update(); 
	_player.update(dt);
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
				entity->get<CBoundingBox>().min.x += velocity.x;
				entity->get<CBoundingBox>().min.y += velocity.y;
				entity->get<CBoundingBox>().max.x += velocity.x;
				entity->get<CBoundingBox>().max.y += velocity.y;
			}
		}
	}
}

void ScenePlay::collisions() {
	CBoundingBox bb = _ball.getEntity()->get<CBoundingBox>();
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CBoundingBox>() && entity->id() != _ball.getEntity()->id()) {
			CBoundingBox bb2 = entity->get<CBoundingBox>();
			// if (CheckCollisionRecs(bb.rect, bb2.rect)) {
			// 	_ball.collision(entity);
			// }
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
		_game_engine.changeScene<SceneMenu>("menu");
	}

	// DEBUG: render bounding boxes
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CBoundingBox>()) {
			CBoundingBox bb = entity->get<CBoundingBox>();
			DrawRectangleLines(bb.min.x, bb.min.y, bb.max.x - bb.min.x, bb.max.y - bb.min.y, RED);
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
