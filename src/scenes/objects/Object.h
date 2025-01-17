#pragma once

#include "../entities/Entity.h"
#include "raymath.h"

class Object {
protected:
	std::shared_ptr<Entity> _entity;

public:
	Object() = default;
	Object(const std::shared_ptr<Entity>& entity) : _entity(entity) {}
	virtual ~Object() = default;

	void init() {}
	void update(const float& dt) {}
	void destroy() { _entity->destroy(); }

	const std::shared_ptr<Entity> getEntity() const { return _entity; }
	
	const Vector2 position() const;
	const Vector2 velocity() const;
};