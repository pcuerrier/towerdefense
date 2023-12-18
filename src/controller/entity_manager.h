#pragma once

#include "../config.h"

#include "../entity.h"

#include <array>
#include <set>
#include <queue>

class EntityManager
{
public:
    EntityManager() = default;
    ~EntityManager() = default;

    ENTITY_ID createEntity();
    void deleteEntity(const ENTITY_ID id);

    bool isEntityActive(const ENTITY_ID id) const;

    // Testing
    uint32_t getCount() const { return _count; }

private:
    std::set<ENTITY_ID> _entities {};
    std::queue<ENTITY_ID> _recycledIDs {};
    uint32_t _count { 0 };
};
