#pragma once

#include "../config.h"

#include "../entity.h"

#include <unordered_map>

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    bool createEntity();
    void deleteEntity(const ENTITY_ID id);

    bool isEntityActive(const ENTITY_ID id) const;

private:
    std::unordered_map<
    std::unordered_map<uint32_t,1000> _entities {};
    uint32_t _count { 0 };
    // TODO: Recycle ids
    uint32_t _lastID { 0 };
};
