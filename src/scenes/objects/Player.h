#pragma once

#include "Paddle.h"

class Player : public Paddle {
	int 	_score = 0;
	int 	_lives = 3;
public:
	Player() = default;
	Player(const std::shared_ptr<Entity>& entity) : Paddle(entity) {}

	void init();
	void update(const float& dt);

	void moveUp();
	void moveDown();
	void stopUp();
	void stopDown();

	void score();
	void die();
	int getLives() const { return _lives; }
};