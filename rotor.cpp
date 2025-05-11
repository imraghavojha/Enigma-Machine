#include "rotor.h"
#include <algorithm>
using namespace std;

// constructor
rotor::rotor(char scram[26], int pos, char init_pos)
{
    // Initialize normal A-Z array internally
    for (int i = 0; i < 26; i++)
    {
        normal[i] = 'A' + i; // Each rotor has its own array
    }

    // Copy scrambled configuration
    for (int i = 0; i < 26; i++)
    {
        scrambled[i] = scram[i];
    }

    // Set other properties
    position = pos;
    init_position = init_pos;

    // Set initial position
    while (normal[0] != init_position)
    {
        rotate_rotor();
    }
}

int rotor::step_through_rotor(int input_position) const
{
    // Forward path (right to left)
    char letter = scrambled[input_position]; // Get letter from scrambled at position

    // Find this letter's position in next rotor's normal array
    for (int i = 0; i < 26; i++)
    {
        if (letter == normal[i])
        {
            return i;
        }
    }
    return -1;
}

int rotor::step_through_rotor_reverse(int input_position) const
{
    // Reverse path (left to right)
    char letter = normal[input_position]; // Get letter from normal at position

    // Find this letter's position in next rotor's scrambled array
    for (int i = 0; i < 26; i++)
    {
        if (letter == scrambled[i])
        {
            return i;
        }
    }
    return -1;
}

void rotor::rotate_column(char y[26])
{
    char first = y[0];
    for (int i = 0; i < 25; i++)
    {
        y[i] = y[i + 1];
    }
    y[25] = first;
}

void rotor::rotate_rotor()
{
    rotate_column(normal);
    rotate_column(scrambled);
    position = (position + 1) % 26;
}

void rotor::reset()
{
    while (normal[0] != init_position)
    {
        rotate_rotor();
    }
}

void rotor::setPosition(char new_position)
{
    // Calculate how many rotations we need
    // First, get back to 'A' position
    while (normal[0] != 'A')
    {
        rotate_rotor();
    }

    // Then rotate until we reach the desired position
    while (normal[0] != new_position)
    {
        rotate_rotor();
    }
}

// getters
int rotor::getPosition() const
{
    return position;
}

char rotor::getCurrentLetter() const
{
    return normal[0];
}