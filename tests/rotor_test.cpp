#include <gtest/gtest.h>
#include "../rotor.h"

// Test fixture for Rotor tests
class RotorTest : public ::testing::Test
{
protected:
    // Historical rotor configuration (Rotor I from Enigma)
    char rotor1_config[26] = {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'};

    // Additional rotor configurations for testing
    char rotor2_config[26] = {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H', 'W', 'T', 'M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'};
    char rotor3_config[26] = {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'};
};

// Test constructor initialization
TEST_F(RotorTest, ConstructorInitialization)
{
    rotor r(rotor1_config, 0, 'A');

    EXPECT_EQ(r.getPosition(), 0);
    EXPECT_EQ(r.getCurrentLetter(), 'A');
}

// Test initialization with different starting position
TEST_F(RotorTest, InitializationWithDifferentPosition)
{
    rotor r(rotor1_config, 0, 'B');

    // The rotor should be rotated to start at 'B'
    EXPECT_EQ(r.getCurrentLetter(), 'B');
    EXPECT_EQ(r.getPosition(), 1);
}

// Test rotor rotation
TEST_F(RotorTest, RotorRotation)
{
    rotor r(rotor1_config, 0, 'A');

    // Initial state
    EXPECT_EQ(r.getPosition(), 0);
    EXPECT_EQ(r.getCurrentLetter(), 'A');

    // Rotate once
    r.rotate_rotor();
    EXPECT_EQ(r.getPosition(), 1);
    EXPECT_EQ(r.getCurrentLetter(), 'B');

    // Rotate multiple times
    for (int i = 0; i < 5; i++)
    {
        r.rotate_rotor();
    }
    EXPECT_EQ(r.getPosition(), 6);
    EXPECT_EQ(r.getCurrentLetter(), 'G');
}

// Test full rotation cycle
TEST_F(RotorTest, FullRotationCycle)
{
    rotor r(rotor1_config, 0, 'A');

    // Rotate 26 times should bring us back to the start
    for (int i = 0; i < 26; i++)
    {
        r.rotate_rotor();
    }

    EXPECT_EQ(r.getPosition(), 0);
    EXPECT_EQ(r.getCurrentLetter(), 'A');
}

// Test step through rotor (forward)
TEST_F(RotorTest, StepThroughRotorForward)
{
    rotor r(rotor1_config, 0, 'A');

    // Test known mappings for Rotor I
    // When input is position 0 (A), it should map to position 4 (E)
    int result = r.step_through_rotor(0);
    EXPECT_EQ(result, 4); // A -> E

    // When input is position 1 (B), it should map to position 10 (K)
    result = r.step_through_rotor(1);
    EXPECT_EQ(result, 10); // B -> K

    // When input is position 2 (C), it should map to position 12 (M)
    result = r.step_through_rotor(2);
    EXPECT_EQ(result, 12); // C -> M
}

// Test step through rotor (reverse)
TEST_F(RotorTest, StepThroughRotorReverse)
{
    rotor r(rotor1_config, 0, 'A');

    // Test reverse mappings
    // If forward is A->E (0->4), then reverse should be E->A (4->0)
    int result = r.step_through_rotor_reverse(4);
    EXPECT_EQ(result, 0); // E -> A

    result = r.step_through_rotor_reverse(10);
    EXPECT_EQ(result, 1); // K -> B

    result = r.step_through_rotor_reverse(12);
    EXPECT_EQ(result, 2); // M -> C
}

// Test reset functionality
TEST_F(RotorTest, Reset)
{
    rotor r(rotor1_config, 0, 'D');

    // Rotate several times
    for (int i = 0; i < 10; i++)
    {
        r.rotate_rotor();
    }

    // Reset should bring it back to initial position 'D'
    r.reset();
    EXPECT_EQ(r.getCurrentLetter(), 'D');
    EXPECT_EQ(r.getPosition(), 3); // D is at position 3
}

// Test setPosition
TEST_F(RotorTest, SetPosition)
{
    rotor r(rotor1_config, 0, 'A');

    // Set to position 'M'
    r.setPosition('M');
    EXPECT_EQ(r.getCurrentLetter(), 'M');
    EXPECT_EQ(r.getPosition(), 12); // M is at position 12

    // Set to position 'Z'
    r.setPosition('Z');
    EXPECT_EQ(r.getCurrentLetter(), 'Z');
    EXPECT_EQ(r.getPosition(), 25); // Z is at position 25
}

// Test step through after rotation
TEST_F(RotorTest, StepThroughAfterRotation)
{
    rotor r(rotor1_config, 0, 'A');

    // Rotate the rotor once
    r.rotate_rotor();

    // Now test stepping through - the mapping should be different
    // After one rotation, what was at position 0 is now at position 25
    int result = r.step_through_rotor(0);

    // The result will depend on how rotation affects the internal state
    // This test verifies that rotation affects the encryption
    EXPECT_NE(result, 4); // Should not be the same as without rotation
}

// Test different rotor configurations
TEST_F(RotorTest, DifferentRotorConfigurations)
{
    rotor r1(rotor1_config, 0, 'A');
    rotor r2(rotor2_config, 0, 'A');
    rotor r3(rotor3_config, 0, 'A');

    // Different rotors should produce different mappings
    EXPECT_NE(r1.step_through_rotor(0), r2.step_through_rotor(0));
    EXPECT_NE(r2.step_through_rotor(0), r3.step_through_rotor(0));
    EXPECT_NE(r1.step_through_rotor(0), r3.step_through_rotor(0));
}

// Test extreme rotation scenarios
TEST_F(RotorTest, ExtensiveRotation)
{
    rotor r(rotor1_config, 0, 'A');

    // Rotate 1000 times and verify it still works correctly
    for (int i = 0; i < 1000; i++)
    {
        r.rotate_rotor();
    }

    // Position should be 1000 % 26
    EXPECT_EQ(r.getPosition(), 1000 % 26);
}

// Test all 26 starting positions
TEST_F(RotorTest, AllStartingPositions)
{
    for (char start = 'A'; start <= 'Z'; start++)
    {
        rotor r(rotor1_config, 0, start);
        EXPECT_EQ(r.getCurrentLetter(), start);

        // Verify reset works for all starting positions
        r.rotate_rotor();
        r.rotate_rotor();
        r.reset();
        EXPECT_EQ(r.getCurrentLetter(), start);
    }
}

// Test boundary conditions for step_through functions
TEST_F(RotorTest, StepThroughBoundaries)
{
    rotor r(rotor1_config, 0, 'A');

    // Test all 26 positions
    for (int i = 0; i < 26; i++)
    {
        int forward = r.step_through_rotor(i);
        EXPECT_GE(forward, 0);
        EXPECT_LE(forward, 25);

        // Verify reverse is truly inverse
        int reverse = r.step_through_rotor_reverse(forward);
        EXPECT_EQ(reverse, i);
    }
}

// Test rotor behavior after many operations
TEST_F(RotorTest, StressTest)
{
    rotor r(rotor1_config, 0, 'A');

    // Perform many random operations
    for (int i = 0; i < 1000; i++)
    {
        if (i % 3 == 0)
            r.rotate_rotor();
        if (i % 5 == 0)
            r.setPosition('A' + (i % 26));
        if (i % 7 == 0)
            r.reset();

        // Always verify state is valid
        EXPECT_GE(r.getPosition(), 0);
        EXPECT_LE(r.getPosition(), 25);
        EXPECT_GE(r.getCurrentLetter(), 'A');
        EXPECT_LE(r.getCurrentLetter(), 'Z');
    }
}