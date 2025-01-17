#pragma once

#include "Object.h"

class Ball : public Object {
public:
	Ball() = default;
	Ball(const std::shared_ptr<Entity>& entity) : Object(entity) {}

	void init();
};