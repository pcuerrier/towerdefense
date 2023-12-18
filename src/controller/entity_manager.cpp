#include "entity_manager.h"

ENTITY_ID EntityManager::createEntity()
{
    if (_count == ENTITY_MAX) { return ENTITY_INVALID; }
    // Try to recyle ID

    ENTITY_ID id = ENTITY_INVALID;
    ++_count;
    if (!_recycledIDs.empty())
    {
        id = _recycledIDs.front();
        _recycledIDs.pop();
    }
    else
    {
        id = _count;
    }
    _entities.insert(id);
    return id;
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
