#pragma once

#include "Entity.h"

class Object {
protected:
	std::shared_ptr<Entity> _entity;

public:
	Object() = default;
	Object(const std::shared_ptr<Entity>& entity) : _entity(entity) {}

	void init() {}
	void update(const float& dt) {}
	void destroy() {}

	const std::shared_ptr<Entity> getEntity() const { return _entity; }
	const Vector2 position() const;
	const Vector2 velocity() const;
};