#pragma once

#include "Object.h"

class Ball : public Object {
	float _speed;
public:
	Ball(Entity* entity);
	~Ball();

	void init();
};