// en vez de ir creando/destruyendo entidades, se pre-aloca memoria para un número máximo de entidades
// esto es más eficiente a la hora de iterar sobre las entidades (cache hits)

// en pong funciona pero a la hora de crear/eliminar entidades no lo he probado, es posible que falle

#pragma once

#include <tuple>
#include <vector>

#include "components/Components.h"
#include "Entity.h"

enum EntityType {
	DEFAULT_ENTITY = -1,
	PLAYER = 0,
	ENEMY = 1,
	BALL = 2,
	WALL = 3,
	GOAL = 4,
	DEATH = 5,
};

// tupla de vectores de componentes para que los componentes estén contiguos en memoria

using EntityComponentVectorTuple = std::tuple<
	std::vector<CTransform>,
	std::vector<CCircleShape>,
	std::vector<CRectShape>,
	std::vector<CInput>,
	std::vector<CBoundingBox>,
	std::vector<CAI>
>;

const size_t MAX_ENTITIES = 100; // si se supera, se debe redimensionar el pool

class EntityMemoryPool {
	size_t 						_num_entities;
	EntityComponentVectorTuple 	_pool;
	std::vector<EntityType> 	_tags;
	std::vector<bool> 			_active;

	EntityMemoryPool(size_t num_entities): // pre-allocate memory for components
		_num_entities(0),
		_pool(),
		_tags(num_entities, EntityType::DEFAULT_ENTITY),
		_active(num_entities, false)
	{
		std::get<std::vector<CTransform>>(_pool).resize(num_entities);
		std::get<std::vector<CCircleShape>>(_pool).resize(num_entities);
		std::get<std::vector<CRectShape>>(_pool).resize(num_entities);
		std::get<std::vector<CInput>>(_pool).resize(num_entities);
		std::get<std::vector<CBoundingBox>>(_pool).resize(num_entities);
		std::get<std::vector<CAI>>(_pool).resize(num_entities);
	}

	friend class EntityManager;
	friend class Entity;

private:
	static EntityMemoryPool& Instance() { // singleton pattern
		static EntityMemoryPool pool(MAX_ENTITIES);
		return pool;
	}

	template<typename T>
	T& getComponent(size_t entityId) {
		return std::get<std::vector<T>>(_pool)[entityId];
	}

	template<typename T>
	bool hasComponent(size_t entityId) {
		return std::get<std::vector<T>>(_pool)[entityId].exists;
	}

	template<typename T>
	void removeComponent(size_t entityId) {
		std::get<std::vector<T>>(_pool)[entityId].exists = false;
	}

	void destroy(size_t entityId) {
		_active[entityId] = false;
	}

	const EntityType& getTag(size_t entityId) const {
		return _tags[entityId];
	}

	bool isActive(size_t entityId) const {
		return _active[entityId];
	}

	size_t addEntity(const EntityType& tag) {
		size_t id = getNextId(); // if no space left, we should resize the pool
		_active[id] = true;
		_tags[id] = tag;
		// TODO: reset components (si no se pueden quedar con los valores de la última entidad y dar problemas)
		return id;
	}

	size_t getNextId() { // encuentra el primer hueco libre en el pool
		for (size_t i = 0; i < _active.size(); ++i) {
			if (!_active[i]) {
				return i;
			}
		}
		return _num_entities++; // should resize the pool
	}
};