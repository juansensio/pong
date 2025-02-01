#pragma once

#include "Paddle.h"
#include "Ball.h"

class Enemy : public Paddle {
	Ball* _ball;
public:
	Enemy(Entity* entity, Ball& ball);
	~Enemy();

	void init();
	void update(const float& dt);
};