#pragma once

#include "../entities/Entity.h"
#include "raymath.h"

class Object {
protected:
	Entity* _entity;

public:
	Object(Entity* entity);
	~Object();

	void init();
	void update(const float& dt);
	void destroy();

	const Entity& getEntity() const { return *_entity; }
	Entity& getEntity() { return *_entity; }
	
	const Vector2 position() const;
	const Vector2 velocity() const;
};