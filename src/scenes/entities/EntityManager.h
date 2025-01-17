#pragma once

#include <vector>
#include <map>
#include "Entity.h"

using EntityList = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<EntityType, EntityList>;

class EntityManager
{
	EntityList 	_entities;
	EntityList 	_newEntities;
	EntityMap 	_entityMap;
	size_t 		_numEntities = 0;

	void removeDeadEntities(EntityList& entities);

public:
	EntityManager() = default;
	~EntityManager() = default;

	void update();

	std::shared_ptr<Entity> addEntity(const EntityType& tag);
	EntityList& getEntities() { return _entities; }
	EntityList& getEntities(const EntityType& tag) { return _entityMap[tag]; }
	const std::map<EntityType, EntityList>& getEntityMap() const { return _entityMap; }
};