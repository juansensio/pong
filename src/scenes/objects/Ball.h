#pragma once

#include "Object.h"

class Ball : public Object {
public:
	Ball(Entity* entity);
	~Ball();

	void init();
};