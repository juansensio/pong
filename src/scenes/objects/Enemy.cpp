#include "Enemy.h"

Enemy::Enemy(Entity* entity, Ball& ball) : Paddle(entity), _ball(&ball) {}

Enemy::~Enemy() {}

void Enemy::init()
{
	Paddle::init(GetScreenWidth() - 10, (float)GetScreenHeight()/2);
}

void Enemy::update(const float& dt)
{
	Vector2 velocity = Vector2Subtract(_ball->getEntity().get<CTransform>().position, _entity->get<CTransform>().position);
	velocity.x = 0;
	velocity = Vector2Normalize(velocity);
	velocity = Vector2Scale(velocity, _speed);
	_entity->get<CTransform>().velocity = velocity;
}
