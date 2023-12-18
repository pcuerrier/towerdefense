#include "gtest/gtest.h"
#include "vector3.h"

TEST(Vector3, create)
{
    // Default
    Vector3 v1 = {};
    Vector3 v2;

    EXPECT_TRUE(v1.x == 0.0f, v1.y == 0.0f, v1.z == 0.0f);
}