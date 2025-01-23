#include "Enemy.h"
#include "../../GameEngine.h"

Enemy::Enemy(Entity* entity) : Paddle(entity) {}

Enemy::~Enemy() {}

void Enemy::init()
{
	_entity->add<CAI>();
	Paddle::init(GetScreenWidth() - 10, (float)GetScreenHeight()/2);
	_speed = 10;
}

void Enemy::update(const float& dt)
{
	if (_entity->has<CAI>()) {
		auto ball = GameEngine::instance().getCurrentScene().getBall();
		Vector2 velocity = Vector2Subtract(ball.getEntity().get<CTransform>().position, _entity->get<CTransform>().position);
		velocity.x = 0;
		velocity = Vector2Normalize(velocity);
		velocity = Vector2Scale(velocity, _speed);
		_entity->get<CTransform>().velocity = velocity;
	}
}
