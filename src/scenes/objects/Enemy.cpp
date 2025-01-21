#include "Enemy.h"
#include "../../GameEngine.h"

void Enemy::init()
{
	_entity->add<CAI>();
	// Paddle::init(GetScreenWidth() - 10, (float)GetScreenHeight()/2);
	Paddle::init(GetScreenWidth() - 10, 100);
	#if _DEBUG
		_speed = 0;
	#endif
}

void Enemy::update(const float& dt)
{
	if (_entity->has<CAI>()) {
		auto& ball = GameEngine::instance().getCurrentScene()->getBall();
		Vector2 velocity = Vector2Subtract(ball.getEntity()->get<CTransform>().position, _entity->get<CTransform>().position);
		velocity.x = 0;
		velocity = Vector2Normalize(velocity);
		velocity = Vector2Scale(velocity, _speed);
		_entity->get<CTransform>().velocity = velocity;
	}
}
