#include <iostream>
#include <algorithm>
using namespace std;

class rotor
{

private:
    char normal[26];
    char scrambled[26];
    int position;
    char init_position;

public:
    // constructor
    rotor(char nor[26], char scram[26], int pos, char init_pos)
    {
        std::copy(nor, nor + 26, normal);
        std::copy(scram, scram + 26, scrambled);
        position = pos;
        init_position = init_pos;
    }

    void init_rotor(char config[26], char init_config = 'A')
    {

        // Initialize normal A-Z array
        for (int i = 0; i < 26; i++)
        {
            normal[i] = 'A' + i;
        }
        // Initialize scrambled array with config
        for (int i = 0; i < 26; i++)
        {
            scrambled[i] = config[i];
        }
        position = 0;
        init_position = init_config; // Store initial position

        while (normal[0] != init_position)
        { // Fixed: using init_position
            rotate_rotor();
        }
    }

    int step_through_rotor(int input_position) const
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

    int step_through_rotor_reverse(int input_position) const
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

    void rotate_column(char y[26])
    {
        char first = y[0];
        for (int i = 0; i < 25; i++)
        {
            y[i] = y[i + 1];
        }
        y[25] = first;
    }

    void rotate_rotor()
    {
        rotate_column(normal);
        rotate_column(scrambled);
        position = (position + 1) % 26;
    }

    void reset()
    {
        while (normal[0] != init_position)
        {
            rotate_rotor();
        }
    }

    void setPosition(char new_position)
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
    int getPosition() const
    {
        return position;
    }

    char getCurrentLetter() const
    {
        return normal[0];
    }
};