#pragma once

#include "Object.h"

class Paddle : public Object {
protected:
	float _paddle_speed;
	
public:
	Paddle(Entity* entity);
	~Paddle();

	void init(const float& x, const float& y);
	void update(const float& dt);
	void collision(const Entity& entity);
};