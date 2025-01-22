#pragma once

#include <vector>
#include <map>

#include "Entity.h"

using EntityList = std::vector<Entity*>;
using EntityMap = std::map<EntityType, EntityList>;

class EntityManager
{
	EntityList 	_entities;
	EntityList 	_new_entities;
	EntityMap 	_entity_map;
	size_t 		_num_entities = 0;

	void removeDeadEntities(EntityList& entities);

public:
	EntityManager();
	~EntityManager();

	void update();

	Entity* addEntity(const EntityType& tag);
	EntityList& getEntities() { return _entities; }
	EntityList& getEntities(const EntityType& tag) { return _entity_map[tag]; }
	const std::map<EntityType, EntityList>& getEntityMap() const { return _entity_map; }
};