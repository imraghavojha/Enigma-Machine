#include <gtest/gtest.h>
#include "../plugboard.h"

// Test fixture for Plugboard tests
class PlugboardTest : public ::testing::Test
{
protected:
    plugboard p;
};

// Test default initialization
TEST_F(PlugboardTest, DefaultInitialization)
{
    // Each letter should map to itself
    for (char c = 'A'; c <= 'Z'; c++)
    {
        EXPECT_EQ(p.getMapping(c), c);
    }

    // Test with indices as well
    for (int i = 0; i < 26; i++)
    {
        EXPECT_EQ(p.getMapping(i), 'A' + i);
    }
}

// Test setting a single plugboard pair
TEST_F(PlugboardTest, SetSinglePair)
{
    p.set_plugboard_pair('A', 'Z');

    // A should map to Z and Z should map to A
    EXPECT_EQ(p.getMapping('A'), 'Z');
    EXPECT_EQ(p.getMapping('Z'), 'A');

    // All other letters should remain unchanged
    for (char c = 'B'; c <= 'Y'; c++)
    {
        EXPECT_EQ(p.getMapping(c), c);
    }
}

// Test setting multiple plugboard pairs
TEST_F(PlugboardTest, SetMultiplePairs)
{
    p.set_plugboard_pair('A', 'Z');
    p.set_plugboard_pair('B', 'Y');
    p.set_plugboard_pair('C', 'X');

    // Check all swaps
    EXPECT_EQ(p.getMapping('A'), 'Z');
    EXPECT_EQ(p.getMapping('Z'), 'A');
    EXPECT_EQ(p.getMapping('B'), 'Y');
    EXPECT_EQ(p.getMapping('Y'), 'B');
    EXPECT_EQ(p.getMapping('C'), 'X');
    EXPECT_EQ(p.getMapping('X'), 'C');

    // Check unchanged letters
    for (char c = 'D'; c <= 'W'; c++)
    {
        EXPECT_EQ(p.getMapping(c), c);
    }
}

// Test overwriting a plugboard pair
TEST_F(PlugboardTest, OverwritePair)
{
    // First set A-Z
    p.set_plugboard_pair('A', 'Z');
    EXPECT_EQ(p.getMapping('A'), 'Z');

    // Now set A-B, which should overwrite A-Z
    p.set_plugboard_pair('A', 'B');
    EXPECT_EQ(p.getMapping('A'), 'B');
    EXPECT_EQ(p.getMapping('B'), 'A');

    // Z should now map to itself (no longer connected to A)
    // Note: This behavior depends on your implementation
}

// Test getting mapping array
TEST_F(PlugboardTest, GetMappingArray)
{
    p.set_plugboard_pair('A', 'Z');

    const char *mapping = p.getMappingArray();

    // First element should be 'Z' (A maps to Z)
    EXPECT_EQ(mapping[0], 'Z');
    // Last element should be 'A' (Z maps to A)
    EXPECT_EQ(mapping[25], 'A');

    // All others should be identity
    for (int i = 1; i < 25; i++)
    {
        EXPECT_EQ(mapping[i], 'A' + i);
    }
}

// Test edge cases
TEST_F(PlugboardTest, EdgeCases)
{
    // Test with same letter (should do nothing or handle gracefully)
    p.set_plugboard_pair('A', 'A');
    EXPECT_EQ(p.getMapping('A'), 'A');

    // Test boundary letters
    p.set_plugboard_pair('A', 'Z');
    EXPECT_EQ(p.getMapping('A'), 'Z');
    EXPECT_EQ(p.getMapping('Z'), 'A');
}

// Test invalid input handling
TEST_F(PlugboardTest, InvalidInputHandling)
{
    // Test with lowercase letters (if your implementation expects uppercase)
    // This depends on whether your implementation handles this or expects caller to validate

    // Test setting same letter to itself
    p.set_plugboard_pair('A', 'A');
    EXPECT_EQ(p.getMapping('A'), 'A');

    // Test overwriting existing pairs
    p.set_plugboard_pair('A', 'B');
    EXPECT_EQ(p.getMapping('A'), 'B');

    // Now connect A to C - what happens to B?
    p.set_plugboard_pair('A', 'C');
    EXPECT_EQ(p.getMapping('A'), 'C');
    // B might now map to itself or still to A - test your implementation's behavior
}

// Test all 26 letters are handled correctly
TEST_F(PlugboardTest, AllLettersMapping)
{
    // Create a complex plugboard setup
    p.set_plugboard_pair('A', 'Z');
    p.set_plugboard_pair('B', 'Y');
    p.set_plugboard_pair('C', 'X');
    p.set_plugboard_pair('D', 'W');

    // Keep track of what maps to what
    std::set<char> mapped_letters;

    // Verify all 26 letters have valid mappings
    for (char c = 'A'; c <= 'Z'; c++)
    {
        char mapped = p.getMapping(c);
        EXPECT_GE(mapped, 'A');
        EXPECT_LE(mapped, 'Z');

        // Verify bidirectional mapping
        if (c != mapped)
        {
            EXPECT_EQ(p.getMapping(mapped), c);
        }
    }
}