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
	_entity->add<CBoundingBox>(
		Vector2{x - radius, y - radius}, 
		Vector2{x + radius, y + radius}
	);
}


void Ball::collision(const std::shared_ptr<Entity>& entity) {
	if (entity->tag() == EntityType::WALL) {
		Vector2 velocity = _entity->get<CTransform>().velocity;
		velocity.y = -velocity.y;
		_entity->get<CTransform>().velocity = velocity;
	} else if (entity->tag() == EntityType::PLAYER || entity->tag() == EntityType::ENEMY) {
		Vector2 velocity = _entity->get<CTransform>().velocity;
		velocity.x = -velocity.x;
		_entity->get<CTransform>().velocity = velocity;
	}
}
	