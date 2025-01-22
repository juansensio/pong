#include "EntityManager.h"

EntityManager::EntityManager() : _numEntities(0) {}

EntityManager::~EntityManager() {
	for (auto e : _entities) {
		delete e;
	}
}

Entity* EntityManager::addEntity(const EntityType& tag) 
{
 	// auto e = std::shared_ptr<Entity>(new Entity(_numEntities++, tag));
	Entity* e = new Entity(_numEntities++, tag);
	_newEntities.push_back(e);
	return e;
}

void EntityManager::update() 
{
	// add new entities (list and map)
	for (auto e : _newEntities)
	{
		_entities.push_back(e);
		_entityMap[e->tag()].push_back(e);
	}
	_newEntities.clear();

	// remove dead entities (list and map)
	removeDeadEntities(_entities);
	for (auto& [tag, entities]: _entityMap)
	{
		removeDeadEntities(entities);
	}
}

void EntityManager::removeDeadEntities(EntityList& entities) 
{
	// get dead entities
	EntityList dead_entities;
	for (auto e : entities)
	{
		if (!e->isAlive()) 
		{
			dead_entities.push_back(e);
		}
	}

	// remove dead entities from list and map
	for (auto& dead_entity : dead_entities) {
        // Find and erase the dead entity from _entities
        auto it = std::find(_entities.begin(), _entities.end(), dead_entity);
        if (it != _entities.end()) {
            _entities.erase(it);
			_numEntities--;
        }

        // remove the entity from _entityMap if necessary
        auto map_it = _entityMap.find(dead_entity->tag());
        if (map_it != _entityMap.end()) {
            auto& map_list = map_it->second;
            map_list.erase(std::remove(map_list.begin(), map_list.end(), dead_entity), map_list.end());
        }
    }
}