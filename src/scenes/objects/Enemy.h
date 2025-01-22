#pragma once

#include "Paddle.h"

class Enemy : public Paddle {
public:
	Enemy(Entity* entity);
	~Enemy();

	void init();
	void update(const float& dt);
};