#include "Player.h"

void Player::init()
{
	Paddle::init(10, (float)GetScreenHeight() / 2);
}

void Player::update(const float& dt)
{
	const auto& input = _entity->get<CInput>();
	if (input.up) {
		_entity->get<CTransform>().velocity.y = - _paddle_speed;
	} else if (input.down) {
		_entity->get<CTransform>().velocity.y = _paddle_speed;
	} else {
		_entity->get<CTransform>().velocity.y = 0;
	}
}


void Player::moveUp()
{
	_entity->get<CInput>().up = true;
}

void Player::moveDown()
{
	_entity->get<CInput>().down = true;
}

void Player::stopUp()
{
	_entity->get<CInput>().up = false;
}

void Player::stopDown()
{
	_entity->get<CInput>().down = false;
}