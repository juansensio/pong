#pragma once

#include "Paddle.h"
#include "Ball.h"

class Enemy : public Paddle {
	Ball* _ball;
public:
	Enemy() : _ball(nullptr) {}
	Enemy(const std::shared_ptr<Entity>& entity, Ball& ball) 
		: Paddle(entity), _ball(&ball) {}

	void init();
	void update(const float& dt);
};