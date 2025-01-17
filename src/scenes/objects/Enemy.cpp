#include "Enemy.h"

void Enemy::init()
{
	Paddle::init(GetScreenWidth() - 10, (float)GetScreenHeight()/2);
}

#include <iostream>

void Enemy::update(const float& dt)
{
	Vector2 velocity = Vector2Subtract(_ball->getEntity()->get<CTransform>().position, _entity->get<CTransform>().position);
	velocity.x = 0;
	velocity = Vector2Normalize(velocity);
	velocity = Vector2Scale(velocity, _speed);
	_entity->get<CTransform>().velocity = velocity;
}
