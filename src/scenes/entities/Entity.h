#pragma once

#include <memory>
#include <tuple>

#include "EntityMemoryPool.h"

class Entity {
	friend class EntityManager; // unica clase que puede crear/destruir entidades

	size_t _id; // al usar memory pool, la entidad simplemente es un id

	Entity(const size_t id): _id(id) {}

public:
	template<typename T>
	T& get() {
		return EntityMemoryPool::Instance().getComponent<T>(_id);
	}
	
	template<typename T>
	T& get() const {
		return EntityMemoryPool::Instance().getComponent<T>(_id);
	}

	template<typename T>
	bool has() {
		return EntityMemoryPool::Instance().hasComponent<T>(_id);
	}

	template<typename T, typename... TArgs>
	T& add(TArgs&&... args) {
		auto& component = EntityMemoryPool::Instance().getComponent<T>(_id);
		component = T(std::forward<TArgs>(args)...);
		component.exists = true;
		return component;
	}

	template<typename T>
	void removeComponent() {
		EntityMemoryPool::Instance().removeComponent<T>(_id);
	}

	void destroy() {
		EntityMemoryPool::Instance().destroy(_id);
	}

	const EntityType& tag() const {
		return EntityMemoryPool::Instance().getTag(_id);
	}

	bool isAlive() const {
		return EntityMemoryPool::Instance().isActive(_id);
	}

	size_t id() const {
		return _id;
	}

	// required for std::find (on delete e)
	friend bool operator==(const Entity& lhs, const Entity& rhs) {
		return lhs._id == rhs._id;
	}
};