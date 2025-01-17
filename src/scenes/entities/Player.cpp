#include "Player.h"

void Player::init()
{
	_entity->add<CTransform>(Vector2{20, (float)GetScreenHeight()/2}, Vector2{300, 0});
	_entity->add<CCircleShape>(10, WHITE);
}

void Player::update(const float& dt)
{
	_entity->get<CTransform>().position.x += _entity->get<CTransform>().velocity.x * dt;
}

void Player::destroy()
{
	_entity->destroy();
}