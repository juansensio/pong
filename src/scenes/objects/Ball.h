#pragma once

#include "Object.h"

class Player;

class Ball : public Object {
	float 		_speed = 600;
public:

	Ball(Entity* entity);
	~Ball();

	void init();
	void collision(const Entity* entity, const Vector2& prevOverlap);

	void setSpeed(float speed) { _speed = speed; }
	float getSpeed() const { return _speed; }
};
