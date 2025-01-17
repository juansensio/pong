#pragma once

#include "Object.h"

class Ball : public Object {
	float _speed;
public:
	Ball() = default;
	Ball(const std::shared_ptr<Entity>& entity) : Object(entity) {}

	void init();
	void collision(const std::shared_ptr<Entity>& entity);
};