#pragma once

#include "Object.h"

class Wall : public Object {
	float _wall_speed;
	
public:
	Wall() = default;
	Wall(const std::shared_ptr<Entity>& entity) : Object(entity) {}

	void init();
	void update(const float& dt);

	void moveUp();
	void moveDown();
	void stop();
};