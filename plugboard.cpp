#include <iostream>
using namespace std;

class plugboard
{
private:
    char mapping[26]; // Renamed from plugboard to avoid confusion

public:
    // Constructor (was init_plugboard)
    plugboard()
    {
        // Initialize with default mapping (no swaps)
        for (int i = 0; i < 26; i++)
        {
            mapping[i] = 'A' + i;
        }
    }

    void set_plugboard_pair(char a, char b)
    {
        // Get array indices
        int a_idx = a - 'A';
        int b_idx = b - 'A';

        // Swap the letters
        mapping[a_idx] = b;
        mapping[b_idx] = a;
    }

    // getting a specific mapping for a character
    char getMapping(char input) const
    {
        int idx = input - 'A';
        return mapping[idx];
    }

    char getMapping(int index) const
    {
        return mapping[index];
    }

    // If you need to get the entire array (returning pointer)
    const char *getMappingArray() const
    {
        return mapping;
    }
};