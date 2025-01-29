#include "Enemy.h"

Enemy::Enemy(Entity* entity) : Paddle(entity) {}

Enemy::~Enemy() {}

void Enemy::init()
{
	Paddle::init(GetScreenWidth() - 10, (float)GetScreenHeight()/2);
}

void Enemy::update(const float& dt) {}
