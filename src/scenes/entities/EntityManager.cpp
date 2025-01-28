#include <algorithm>

#include "EntityManager.h"

EntityManager::EntityManager() : _num_entities(0) {}

EntityManager::~EntityManager() {
	for (auto e : _entities) {
		delete e;
	}
}

Entity* EntityManager::addEntity(const EntityType& tag) 
{
	size_t id = EntityMemoryPool::Instance().addEntity(tag);
	Entity* e = new Entity(id);
	_new_entities.push_back(e);
	return e;
}

void EntityManager::update() 
{
	// add new entities (list and map)
	for (auto e : _new_entities)
	{
		_entities.push_back(e);
		_entity_map[e->tag()].push_back(e);
	}
	_new_entities.clear();

	// remove dead entities (list and map)
	removeDeadEntities(_entities);
	for (auto& [tag, entities]: _entity_map)
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
			_num_entities--;
        }

        // remove the entity from _entity_map if necessary
        auto map_it = _entity_map.find(dead_entity->tag());
        if (map_it != _entity_map.end()) {
            auto& map_list = map_it->second;
            map_list.erase(std::remove(map_list.begin(), map_list.end(), dead_entity), map_list.end());
        }
    }
}