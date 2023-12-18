#include "gtest/gtest.h"
#include "controller/entity_manager.h"

#include <cstdlib>
#include <queue>

TEST(EntityManager, create_and_delete)
{
    EntityManager e;

    EXPECT_EQ(e.createEntity(), 1);
    EXPECT_TRUE(e.isEntityActive(1));

    EXPECT_EQ(e.createEntity(), 2);
    EXPECT_TRUE(e.isEntityActive(2));

    EXPECT_EQ(e.createEntity(), 3);
    EXPECT_TRUE(e.isEntityActive(3));

    EXPECT_EQ(e.createEntity(), 4);
    EXPECT_TRUE(e.isEntityActive(4));

    EXPECT_EQ(e.getCount(), 4);

    e.deleteEntity(1);
    EXPECT_FALSE(e.isEntityActive(1));

    e.deleteEntity(2);
    EXPECT_FALSE(e.isEntityActive(2));

    e.deleteEntity(3);
    EXPECT_FALSE(e.isEntityActive(3));

    e.deleteEntity(4);
    EXPECT_FALSE(e.isEntityActive(4));

    EXPECT_EQ(e.getCount(), 0);

    // Delete non-existen id
    e.deleteEntity(1);
    e.deleteEntity(2);
    e.deleteEntity(3);
    e.deleteEntity(4);
    EXPECT_EQ(e.getCount(), 0);
}

TEST(EntityManager, max_entities)
{
    EntityManager e;

    for (uint32_t i = 0; i < ENTITY_MAX; ++i)
    {
        EXPECT_EQ(e.createEntity(), i + 1);
    }
    EXPECT_EQ(e.getCount(), ENTITY_MAX);
    EXPECT_EQ(e.createEntity(), ENTITY_INVALID);
}

TEST(EntityManager, recycling_ids)
{
    EntityManager e;

    for (uint32_t i = 0; i < 10; ++i)
    {
        EXPECT_EQ(e.createEntity(), 1);
        e.deleteEntity(1);
        EXPECT_FALSE(e.isEntityActive(1));

    }
    EXPECT_EQ(e.getCount(), 0);

    for (uint32_t i = 0; i < 10; ++i)
    {
        EXPECT_EQ(e.createEntity(), i + 1);
        EXPECT_TRUE(e.isEntityActive(i + 1));
    }
    e.deleteEntity(3);
    EXPECT_FALSE(e.isEntityActive(3));

    e.deleteEntity(7);
    EXPECT_FALSE(e.isEntityActive(7));

    e.deleteEntity(1);
    EXPECT_FALSE(e.isEntityActive(1));

    EXPECT_EQ(e.createEntity(), 3);
    EXPECT_TRUE(e.isEntityActive(3));

    EXPECT_EQ(e.createEntity(), 7);
    EXPECT_TRUE(e.isEntityActive(7));

    EXPECT_EQ(e.createEntity(), 1);
    EXPECT_TRUE(e.isEntityActive(1));
}
