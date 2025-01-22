#include "Ball.h"

Ball::Ball(Entity* entity) : Object(entity) {}

Ball::~Ball() {}

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
	_entity->add<CBoundingBox>(Vector2{radius*2, radius*2});
}



void Ball::collision(const Entity* entity, const Vector2& prevOverlap) {
	if (entity->tag() == EntityType::WALL) {
		Vector2 velocity = _entity->get<CTransform>().velocity;
		velocity.y = -velocity.y;
		_entity->get<CTransform>().velocity = velocity;
	} else if (entity->tag() == EntityType::PLAYER || entity->tag() == EntityType::ENEMY) {
		if (prevOverlap.x > 0 && prevOverlap.y <= 0) { // top/bottom collision
			Vector2 velocity = _entity->get<CTransform>().velocity;
			velocity.y = -velocity.y;
			_entity->get<CTransform>().velocity = velocity;
		} else { // side and diagonal collision
			Vector2 velocity = _entity->get<CTransform>().velocity;
			velocity.x = -velocity.x;
			_entity->get<CTransform>().velocity = velocity;
		}
	}
}
	
