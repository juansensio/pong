#pragma once

#include "Object.h"

class Goal : public Object {
	
public:
	Goal() = default;
	Goal(const std::shared_ptr<Entity>& entity) : Object(entity) {}

	void init();
};