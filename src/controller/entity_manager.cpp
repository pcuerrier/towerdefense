#include "entity_manager.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

bool EntityManager::createEntity()
{
    if (_count == ENTITY_MAX) { return false; }
    _entities[_count++] = ++_lastID;
}

void EntityManager::deleteEntity(const ENTITY_ID id)
{
    ENTITY_ID temp = _entities[]
    _entities[id] = ENTITY_ID;
}

bool EntityManager::isEntityActive(const ENTITY_ID id) const
{
    return _entities[id] != ENTITY_INVALID;
}