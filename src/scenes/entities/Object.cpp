#include <stdexcept>

#include "Object.h"

Object::Object(Entity* entity) : _entity(entity) {}

Object::~Object() {}

void Object::init() {}

void Object::update(const float& dt) {}

void Object::destroy() { _entity->destroy(); }

const Vector2 Object::position() const
{
	if (_entity->has<CTransform>()) return _entity->get<CTransform>().position;
	throw std::runtime_error("Object has no transform");
}

const Vector2 Object::velocity() const
{
	if (_entity->has<CTransform>()) return _entity->get<CTransform>().velocity;
	throw std::runtime_error("Object has no transform");
}