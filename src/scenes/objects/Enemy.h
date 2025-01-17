#pragma once

#include "Paddle.h"

class Enemy : public Paddle {
public:
	Enemy() = default;
	Enemy(const std::shared_ptr<Entity>& entity) : Paddle(entity) {}

	void init();
	void update(const float& dt);
};