#pragma once

#include <memory>

enum EntityType {
	PLAYER = 0,
};

class Entity
{
	friend class EntityManager; // de esta manera es la unica clase que puede crear entidades

	EntityType 	_tag;
	size_t 		_id;
	bool 		_isAlive;

	// TODO: components

	Entity(const size_t& id, const EntityType& tag) : _tag(tag), _id(id), _isAlive(true) {}

public:

	float x;
	float v; 

	const EntityType& tag() const { return _tag; }
	size_t id() const { return _id; }
	bool isAlive() const { return _isAlive; }
	void destroy() { _isAlive = false; }
};