#include "Player.h"
#include "../../GameEngine.h"

void Player::init()
{
	Paddle::init(10, (float)GetScreenHeight() / 2);
	_entity->add<CAI>();
}

void Player::update(const float& dt)
{
	if (_entity->has<CAI>()) {
		auto ball = GameEngine::instance().getCurrentScene()->getBall();
		Vector2 velocity = Vector2Subtract(ball.getEntity()->get<CTransform>().position, _entity->get<CTransform>().position);
		velocity.x = 0;
		velocity = Vector2Normalize(velocity);
		velocity = Vector2Scale(velocity, _speed);
		_entity->get<CTransform>().velocity = velocity;
	} else {
		const auto& input = _entity->get<CInput>();
		if (input.up) {
			_entity->get<CTransform>().velocity.y = - _speed;
		} else if (input.down) {
			_entity->get<CTransform>().velocity.y = _speed;
		} else {
			_entity->get<CTransform>().velocity.y = 0;
		}
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

void Player::score() {
	auto& levelManager = GameEngine::instance().getCurrentScene()->getLevelManager();
	_score++;
	if (_score >= levelManager.getLevel().getGoalsForNextLevel()) {
		levelManager.loadNextLevel();
	}
}

void Player::die() {
	_lives--;
}