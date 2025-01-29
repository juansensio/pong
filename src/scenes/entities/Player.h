#pragma once

#include "Paddle.h"

class Player : public Paddle {
public:
	Player(Entity* entity);
	~Player();

	void init();
	void update(const float& dt);

	void moveUp();
	void moveDown();
	void stopUp();
	void stopDown();
};