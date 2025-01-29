#pragma once

#include "Object.h"

class Wall : public Object {
	float _wall_speed;
	
public:
	Wall(Entity* entity);
	~Wall();
	
	void init();
	void update(const float& dt);

	void moveUp();
	void moveDown();
	void stop();
};