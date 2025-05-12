#include <gtest/gtest.h>
#include "../plugboard.h"

// The simplest possible test
TEST(PlugboardTest, CanCreatePlugboard)
{
    plugboard p;
    EXPECT_TRUE(true); // This test just verifies everything compiles
}

// Test the default initialization
TEST(PlugboardTest, DefaultInitialization)
{
    plugboard p;
    // Letter A should map to itself by default
    EXPECT_EQ(p.getMapping('A'), 'A');
}