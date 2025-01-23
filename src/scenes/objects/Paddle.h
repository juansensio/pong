#pragma once

#include "Object.h"

class Paddle : public Object {
protected:
	float 	_speed;

public:
	Paddle(Entity* entity);
	~Paddle();

	void init(const float& x, const float& y);
	void update(const float& dt);
	void collision(const Entity& entity);

	void setSpeed(float speed) { _speed = speed; }
	float getSpeed() const { return _speed; }
};