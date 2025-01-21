#pragma once

#include "Object.h"

class Player;

class Ball : public Object {
	float 		_speed = 300;
public:
	Ball() = default;
	Ball(const std::shared_ptr<Entity>& entity) : Object(entity) {}

	void init();
	void collision(const std::shared_ptr<Entity>& entity, const Vector2& prevOverlap);

	void setSpeed(float speed) { _speed = speed; }
	float getSpeed() const { return _speed; }
};