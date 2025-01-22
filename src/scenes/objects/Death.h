#pragma once

#include "Object.h"

class Death : public Object {
	
public:
	Death(Entity* entity);
	~Death();

	void init();
};