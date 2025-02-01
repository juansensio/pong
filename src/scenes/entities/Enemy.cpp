#include "Enemy.h"

Enemy::Enemy(Entity* entity, Ball& ball) : Paddle(entity), _ball(&ball) {}

Enemy::~Enemy() {}

void Enemy::init()
{
	Paddle::init(GetScreenWidth() - 10, (float)GetScreenHeight()/2);
	_entity->add<CAI>(_speed);
}

void Enemy::update(const float& dt)
{
	
}
