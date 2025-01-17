#pragma once

#include "Object.h"
#include "Player.h"

class Ball : public Object {
	float 		_speed;
	Player*		_player;
	
public:
	Ball() : _player(nullptr) {}
	Ball(const std::shared_ptr<Entity>& entity, Player& player) 
		: Object(entity), _player(&player) {}

	void init();
	void collision(const std::shared_ptr<Entity>& entity, const Vector2& prevOverlap);
};