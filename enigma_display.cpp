#include "enigma_machine.h"
#include <iostream>
using namespace std;

// constructor
enigma_machine::enigma_machine(char rotor1_config[26], char rotor2_config[26], char rotor3_config[26], char reflector_config[26])
    : right(rotor1_config, 0, 'A'),
      middle(rotor2_config, 0, 'A'),
      left(rotor3_config, 0, 'A'),
      reflector(reflector_config, 0, 'A')
{
    position = 0;
}

void enigma_machine::check_and_rotate_rotors()
{

    if (right.getPosition() == 25)
    { // positions are 0-25
        middle.rotate_rotor();
    }
    if (middle.getPosition() == 25)
    {
        left.rotate_rotor();
    }
    right.rotate_rotor(); // right rotor always rotates
}

void enigma_machine::reset_rotors()
{
    left.reset();
    middle.reset();
    right.reset();
}

char enigma_machine::encrypt_letter(char input)
{

    // 1. First plugboard transformation
    position = input - 'A';
    char first_swap = pb.getMapping(position); // Changed from 'plugboard' to 'pb'
    position = first_swap - 'A';

    // 2. Rotate rotors first (do this before encryption)
    check_and_rotate_rotors();

    // 3. Forward path through rotors
    position = right.step_through_rotor(position);
    position = middle.step_through_rotor(position);
    position = left.step_through_rotor(position);

    // 4. Through reflector
    position = reflector.step_through_rotor(position);

    // 5. Reverse path through rotors
    position = left.step_through_rotor_reverse(position);
    position = middle.step_through_rotor_reverse(position);
    position = right.step_through_rotor_reverse(position);

    // 6. Second plugboard transformation
    return pb.getMapping(position); // Changed from 'plugboard' to 'pb'
}

string enigma_machine::encrypt_message(string message)
{
    string result = "";

    for (int i = 0; i < message.length(); i++)
    {
        char encrypted_letter = encrypt_letter(message[i]);
        result += encrypted_letter;
    }

    return result;
}

void enigma_machine::set_rotor_positions(char l, char m, char r)
{
    left.setPosition(l);
    middle.setPosition(m);
    right.setPosition(r);
}

void enigma_machine::set_plugboard_pair(char a, char b)
{
    pb.set_plugboard_pair(a, b); // Changed from 'plugboard' to 'pb'
}

string enigma_machine::get_rotor_positions() const
{
    string positions = "";
    positions += left.getCurrentLetter();
    positions += middle.getCurrentLetter();
    positions += right.getCurrentLetter();
    return positions;
}