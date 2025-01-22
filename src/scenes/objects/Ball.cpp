#include "Ball.h"

Ball::Ball(Entity* entity) : Object(entity) {}

Ball::~Ball() {}

void Ball::init()
{
	_entity->add<CTransform>(Vector2{20, (float)GetScreenHeight()/2}, Vector2{300, 0});
	_entity->add<CCircleShape>(10, WHITE);
}

void Ball::update(const float& dt)
{
	_entity->get<CTransform>().position.x += _entity->get<CTransform>().velocity.x * dt;
}