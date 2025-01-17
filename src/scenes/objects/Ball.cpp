#include "Ball.h"

void Ball::init()
{
	float x = (float)GetScreenWidth()/2;
	float y = (float)GetScreenHeight()/2;
	float radius = 10;

	_speed = 300;

	_entity->add<CTransform>(
		Vector2{x, y}, 
		Vector2{_speed * (rand() % 2 ? 1 : -1), _speed * (rand() % 2 ? 1 : -1)}
	);
	_entity->add<CCircleShape>(radius, WHITE);
	_entity->add<CBoundingBox>(Rectangle{x - radius, y - radius, radius * 2, radius * 2});
}
