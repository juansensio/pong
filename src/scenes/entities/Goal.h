#pragma once

#include "Object.h"

class Goal : public Object {
	
public:
	Goal(Entity* entity);
	~Goal();

	void init();
};