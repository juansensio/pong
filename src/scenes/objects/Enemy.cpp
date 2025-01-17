#include "Enemy.h"

void Enemy::init()
{
	Paddle::init(GetScreenWidth() - 10, (float)GetScreenHeight()/2);
}

void Enemy::update(const float& dt)
{
}
