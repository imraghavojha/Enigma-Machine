// File: enigma_machine.h
#ifndef ENIGMA_MACHINE_H
#define ENIGMA_MACHINE_H

#include "rotor.h"
#include "plugboard.h"
#include <string>

class enigma_machine
{
private:
    rotor right, middle, left, reflector;
    plugboard pb; // Changed from 'plugboard' to 'pb' to avoid naming conflict
    int position;

public:
    // Constructor
    enigma_machine(char rotor1_config[26], char rotor2_config[26],
                   char rotor3_config[26], char reflector_config[26]);

    // Methods
    void check_and_rotate_rotors();
    void reset_rotors();
    char encrypt_letter(char input);
    std::string encrypt_message(std::string message);
    void set_rotor_positions(char l, char m, char r);
    void set_plugboard_pair(char a, char b);
    std::string get_rotor_positions() const;
};

#endif // ENIGMA_MACHINE_H