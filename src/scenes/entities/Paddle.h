#pragma once

#include "Object.h"

class Paddle : public Object {
protected:
	float _paddle_speed;
	
public:
	Paddle(Entity* entity);
	~Paddle();

	void init();
	void update(const float& dt);
};