#pragma once

#include "Object.h"

class Player : public Object {
public:
	Player() = default;
	Player(const std::shared_ptr<Entity>& entity) : Object(entity) {}

	void init();
	void update(const float& dt);
};