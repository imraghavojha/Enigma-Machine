// File: rotor.h
#ifndef ROTOR_H // Include guard
#define ROTOR_H

class rotor
{
private:
    // Private data members
    char normal[26];
    char scrambled[26];
    int position;
    char init_position;

public:
    // Constructor declaration
    rotor(char scram[26], int pos, char init_pos);

    // Method declarations
    int step_through_rotor(int input_position) const;
    int step_through_rotor_reverse(int input_position) const;
    void rotate_column(char y[26]);
    void rotate_rotor();
    void reset();
    void setPosition(char new_position);

    // Getter method declarations
    int getPosition() const;
    char getCurrentLetter() const;
};

#endif // ROTOR_H