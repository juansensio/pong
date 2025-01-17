#include "Ball.h"

void Ball::init()
{
	_entity->add<CTransform>(Vector2{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, Vector2{0, 0});
	_entity->add<CCircleShape>(10, WHITE);
}
