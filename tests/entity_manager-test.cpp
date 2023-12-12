#include "gtest/gtest.h"
#include "controller/entity_manager.h"

TEST(EntityManager, createEntity)
{
    EntityManager e;

    EXPECT_TRUE(e.createEntity());
    EXPECT_TRUE(e.createEntity());
    EXPECT_TRUE(e.createEntity());
    EXPECT_TRUE(e.createEntity());
    EXPECT_EQ(e.getCount(), 4);
}