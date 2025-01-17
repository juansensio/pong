#pragma once

#include <memory>
#include <tuple>

#include "components/Components.h"

enum EntityType {
	PLAYER = 0,
	WALL = 1
};

using ComponentTuple = std::tuple<
	CTransform,
	CCircleShape,
	CRectShape
>;

class Entity
{
	// friend class EntityManager; // de esta manera es la unica clase que puede crear entidades

	ComponentTuple 		_components;
	EntityType 			_tag;
	size_t 				_id;
	bool 				_isAlive;


public:
	Entity(const size_t& id, const EntityType& tag) : _tag(tag), _id(id), _isAlive(true) {}

	const EntityType& tag() const { return _tag; }
	size_t id() const { return _id; }
	bool isAlive() const { return _isAlive; }
	void destroy() { _isAlive = false; }

	template<typename T, typename... TArgs> 
	T& add(TArgs&&... args) {
		auto& component = std::get<T>(_components);
		component = T(std::forward<TArgs>(args)...);
		component.exists = true;
		return component;
	}

	template<typename T> 
	T& get() { 
		return std::get<T>(_components); 
	}

	template<typename T> 
	const T& get() const { 
		return std::get<T>(_components); 
	}

	template<typename T> 
	bool has() const { 
		return std::get<T>(_components).exists; 
	}
	
	template<typename T> 
	void remove() { 
		std::get<T>(_components) = T(); 
	}
};