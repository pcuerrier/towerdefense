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
    // Try to recyle ID
    if (!_recycledIDs.empty())
    {
        ENTITY_ID id = _recycledIDs.front();
        _recycledIDs.pop();
        _entities.insert(id);
        ++_count;
    }
    else
    {
        _entities.insert(++_count);
    }
    return true;
}

void EntityManager::deleteEntity(const ENTITY_ID id)
{
    size_t ret = _entities.erase(id);
    if (ret)
    {
        _recycledIDs.push(id);
        --_count;
    }
}

bool EntityManager::isEntityActive(const ENTITY_ID id) const
{
    return _entities.find(id) != _entities.end();
}