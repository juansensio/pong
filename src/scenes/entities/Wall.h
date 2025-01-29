#pragma once

#include "Object.h"

class Wall : public Object {
public:
	Wall(Entity* entity);
	~Wall();
	
	void init();
};