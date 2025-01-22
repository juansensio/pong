#include "Enemy.h"

Enemy::Enemy(Entity* entity) : Paddle(entity) {}

Enemy::~Enemy() {}

void Enemy::init()
{
	Paddle::init();
}

void Enemy::update(const float& dt) {}
