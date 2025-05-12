#include <gtest/gtest.h>
#include "../enigma_machine.h"
#include <string>

// Test fixture for EnigmaMachine tests
class EnigmaMachineTest : public ::testing::Test
{
protected:
    // Historical rotor configurations
    char rotor1_config[26] = {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'};
    char rotor2_config[26] = {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H', 'W', 'T', 'M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'};
    char rotor3_config[26] = {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'};
    char reflector_config[26] = {'E', 'J', 'M', 'Z', 'A', 'L', 'Y', 'X', 'V', 'B', 'W', 'F', 'C', 'R', 'Q', 'U', 'O', 'N', 'T', 'S', 'P', 'I', 'K', 'H', 'G', 'D'};

    enigma_machine *machine;

    void SetUp() override
    {
        machine = new enigma_machine(rotor1_config, rotor2_config, rotor3_config, reflector_config);
    }

    void TearDown() override
    {
        delete machine;
    }
};

// Test initialization
TEST_F(EnigmaMachineTest, Initialization)
{
    EXPECT_EQ(machine->get_rotor_positions(), "AAA");
}

// Test setting rotor positions
TEST_F(EnigmaMachineTest, SetRotorPositions)
{
    machine->set_rotor_positions('X', 'Y', 'Z');
    EXPECT_EQ(machine->get_rotor_positions(), "XYZ");

    machine->set_rotor_positions('A', 'B', 'C');
    EXPECT_EQ(machine->get_rotor_positions(), "ABC");
}

// Test single letter encryption
TEST_F(EnigmaMachineTest, EncryptSingleLetter)
{
    // Reset to known state
    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');

    // Encrypt a single letter
    char result = machine->encrypt_letter('A');

    // The result should not be 'A' (no letter encrypts to itself in Enigma)
    EXPECT_NE(result, 'A');

    // Result should be a valid letter
    EXPECT_GE(result, 'A');
    EXPECT_LE(result, 'Z');
}

// Test reciprocal property
TEST_F(EnigmaMachineTest, ReciprocalProperty)
{
    // Reset to known state
    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');

    // Encrypt a letter
    char original = 'X';
    char encrypted = machine->encrypt_letter(original);

    // Reset and encrypt the result - should get back the original
    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');
    char decrypted = machine->encrypt_letter(encrypted);

    EXPECT_EQ(decrypted, original);
}

// Test message encryption
TEST_F(EnigmaMachineTest, EncryptMessage)
{
    std::string message = "HELLO";

    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');
    std::string encrypted = machine->encrypt_message(message);

    // Encrypted message should be same length
    EXPECT_EQ(encrypted.length(), message.length());

    // Should not be the same as original
    EXPECT_NE(encrypted, message);

    // Each character should be valid
    for (char c : encrypted)
    {
        EXPECT_GE(c, 'A');
        EXPECT_LE(c, 'Z');
    }
}

// Test message decryption
TEST_F(EnigmaMachineTest, DecryptMessage)
{
    std::string original = "ENIGMA";

    // Encrypt
    machine->reset_rotors();
    machine->set_rotor_positions('B', 'C', 'D');
    std::string encrypted = machine->encrypt_message(original);

    // Decrypt (encrypt again with same settings)
    machine->reset_rotors();
    machine->set_rotor_positions('B', 'C', 'D');
    std::string decrypted = machine->encrypt_message(encrypted);

    EXPECT_EQ(decrypted, original);
}

// Test plugboard integration
TEST_F(EnigmaMachineTest, PlugboardIntegration)
{
    // Encrypt without plugboard
    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');
    char without_plugboard = machine->encrypt_letter('A');

    // Set plugboard and encrypt
    machine->set_plugboard_pair('A', 'B');
    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');
    char with_plugboard = machine->encrypt_letter('A');

    // Results should be different
    EXPECT_NE(with_plugboard, without_plugboard);
}

// Test rotor stepping
TEST_F(EnigmaMachineTest, RotorStepping)
{
    machine->set_rotor_positions('A', 'A', 'A');

    // Encrypt several letters to see rotor movement
    std::string initial_positions = machine->get_rotor_positions();

    // Encrypt one letter
    machine->encrypt_letter('A');
    std::string after_one = machine->get_rotor_positions();

    // Right rotor should have moved
    EXPECT_NE(initial_positions, after_one);
    EXPECT_EQ(after_one[0], 'A'); // Left rotor shouldn't move yet
    EXPECT_EQ(after_one[1], 'A'); // Middle rotor shouldn't move yet
    EXPECT_EQ(after_one[2], 'B'); // Right rotor should be at B
}

// Test reset functionality - CORRECTED VERSION
TEST_F(EnigmaMachineTest, ResetRotors)
{
    // Initial state after construction is AAA
    EXPECT_EQ(machine->get_rotor_positions(), "AAA");

    // Set new positions
    machine->set_rotor_positions('X', 'Y', 'Z');
    EXPECT_EQ(machine->get_rotor_positions(), "XYZ");

    // Encrypt some letters to change positions
    machine->encrypt_message("TEST");

    // Positions should have changed from XYZ
    std::string after_encryption = machine->get_rotor_positions();
    EXPECT_NE(after_encryption, "XYZ");

    // Reset brings rotors back to their initial construction state (AAA)
    // NOT to the last set position (XYZ)
    machine->reset_rotors();
    EXPECT_EQ(machine->get_rotor_positions(), "AAA");
}

// Additional test to clarify reset behavior
TEST_F(EnigmaMachineTest, ResetAlwaysGoesToConstructionState)
{
    // Set positions to something
    machine->set_rotor_positions('B', 'C', 'D');
    EXPECT_EQ(machine->get_rotor_positions(), "BCD");

    // Reset always goes back to AAA (construction state)
    machine->reset_rotors();
    EXPECT_EQ(machine->get_rotor_positions(), "AAA");

    // Even if we set different positions and reset again
    machine->set_rotor_positions('X', 'Y', 'Z');
    machine->reset_rotors();
    EXPECT_EQ(machine->get_rotor_positions(), "AAA");
}

// Test long message
TEST_F(EnigmaMachineTest, LongMessage)
{
    std::string message = "THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG";

    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');
    std::string encrypted = machine->encrypt_message(message);

    EXPECT_EQ(encrypted.length(), message.length());
    EXPECT_NE(encrypted, message);

    // Decrypt
    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');
    std::string decrypted = machine->encrypt_message(encrypted);

    EXPECT_EQ(decrypted, message);
}

// Test different rotor settings produce different results
TEST_F(EnigmaMachineTest, DifferentSettingsProduceDifferentResults)
{
    std::string message = "TEST";

    // First encryption with AAA
    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');
    std::string result1 = machine->encrypt_message(message);

    // Second encryption with BBB
    machine->reset_rotors();
    machine->set_rotor_positions('B', 'B', 'B');
    std::string result2 = machine->encrypt_message(message);

    // Results should be different
    EXPECT_NE(result1, result2);
}

// Test that no letter encrypts to itself
TEST_F(EnigmaMachineTest, NoLetterEncryptsToItself)
{
    machine->reset_rotors();
    machine->set_rotor_positions('A', 'A', 'A');

    // Test every letter of the alphabet
    for (char letter = 'A'; letter <= 'Z'; letter++)
    {
        machine->reset_rotors();
        machine->set_rotor_positions('A', 'A', 'A');
        char encrypted = machine->encrypt_letter(letter);
        EXPECT_NE(encrypted, letter) << "Letter " << letter << " should not encrypt to itself";
    }
}

// Test rotor turnover behavior
TEST_F(EnigmaMachineTest, RotorTurnoverBehavior)
{
    // Set right rotor to position just before turnover
    machine->set_rotor_positions('A', 'A', 'Y');

    // Encrypt two letters - this should cause right rotor to turn over
    machine->encrypt_letter('A');
    machine->encrypt_letter('A');

    std::string positions = machine->get_rotor_positions();

    // After two encryptions from Y:
    // Right rotor: Y -> Z -> A (turnover)
    // Middle rotor should have advanced once due to turnover
    EXPECT_EQ(positions[2], 'A'); // Right rotor wrapped around
    EXPECT_EQ(positions[1], 'B'); // Middle rotor advanced
    EXPECT_EQ(positions[0], 'A'); // Left rotor unchanged
}