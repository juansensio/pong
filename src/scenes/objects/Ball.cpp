#include "Ball.h"

void Ball::init()
{
	float x = (float)GetScreenWidth()/2;
	float y = (float)GetScreenHeight()/2;
	float radius = 5;

	_speed = 300;

	_entity->add<CTransform>(
		Vector2{x, y}, 
		Vector2{_speed * (rand() % 2 ? 1 : -1), _speed * (rand() % 2 ? 1 : -1)}
	);
	_entity->add<CCircleShape>(radius, WHITE);
	_entity->add<CBoundingBox>(Rectangle{x - radius, y - radius, radius * 2, radius * 2});
}

#include <iostream>

void Ball::collision(const std::shared_ptr<Entity>& entity) {
	if (entity->tag() == EntityType::WALL) {
		Vector2 velocity = _entity->get<CTransform>().velocity;
		velocity.y = -velocity.y;
		_entity->get<CTransform>().velocity = velocity;
	} else if (entity->tag() == EntityType::PLAYER || entity->tag() == EntityType::ENEMY) {
		Vector2 velocity = _entity->get<CTransform>().velocity;
		velocity.x = -velocity.x;
		_entity->get<CTransform>().velocity = velocity;
	} else if (entity->tag() == EntityType::GOAL) {
		_player->score(); // pq esta al reves ??
		init();
	} else if (entity->tag() == EntityType::DEATH) {
		_player->die();
		init();
	}
}
