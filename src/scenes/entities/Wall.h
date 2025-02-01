#pragma once

#include "Object.h"

class Wall : public Object {
public:
	Wall(Entity* entity);
	~Wall();
	
	void init(const float& y);
	void update(const float& dt);
};