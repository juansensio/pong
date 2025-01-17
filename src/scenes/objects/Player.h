#pragma once

#include "Paddle.h"

class Player : public Paddle {
public:
	Player() = default;
	Player(const std::shared_ptr<Entity>& entity) : Paddle(entity) {}

	void init();
	void update(const float& dt);

	void moveUp();
	void moveDown();
	void stop();
};