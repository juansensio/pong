#pragma once

#include "Object.h"

class Paddle : public Object {
protected:
	float _speed;
	
public:
	Paddle() = default;
	Paddle(const std::shared_ptr<Entity>& entity) : Object(entity), _speed(0.0f) {}

	void init(const float& x, const float& y);
	void update(const float& dt);
	void collision(const std::shared_ptr<Entity>& entity);
};