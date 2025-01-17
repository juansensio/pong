#pragma once

#include "Object.h"

class Death : public Object {
	
public:
	Death() = default;
	Death(const std::shared_ptr<Entity>& entity) : Object(entity) {}

	void init();
};