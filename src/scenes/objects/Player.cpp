#include "Player.h"

Player::Player(Entity* entity) : Paddle(entity) {}

Player::~Player() {}

void Player::init()
{
	Paddle::init();
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

void Player::stop()
{
	_entity->get<CInput>().up = false;
	_entity->get<CInput>().down = false;
}