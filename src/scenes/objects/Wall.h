#pragma once

#include "Object.h"

class Wall : public Object {
public:
	Wall() = default;
	Wall(const std::shared_ptr<Entity>& entity) : Object(entity) {}

	void init(const float& y);
};