#pragma once

#include "Object.h"

class Paddle : public Object {
protected:
	float _paddle_speed;
	
public:
	Paddle() = default;
	Paddle(const std::shared_ptr<Entity>& entity) : Object(entity) {}

	void init();
	void update(const float& dt);
};