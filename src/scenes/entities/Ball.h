#pragma once

#include "Object.h"
#include "Player.h"

class Ball : public Object {
	float 		_speed;
	Player*		_player;
	
public:
	Ball(Entity* entity, Player& player);
	~Ball();

	void init();
	void collision(const Entity* entity, const Vector2& prevOverlap);
};
