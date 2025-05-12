#include "plugboard.h"
#include <iostream>
using namespace std;

// Constructor (was init_plugboard)
plugboard::plugboard()
{
    // Initialize with default mapping (no swaps)
    for (int i = 0; i < 26; i++)
    {
        mapping[i] = 'A' + i;
    }
}

void plugboard::set_plugboard_pair(char a, char b)
{
    // Get array indices
    int a_idx = a - 'A';
    int b_idx = b - 'A';

    // Swap the letters
    mapping[a_idx] = b;
    mapping[b_idx] = a;
}

// getting a specific mapping for a character
char plugboard::getMapping(char input) const
{
    int idx = input - 'A';
    return mapping[idx];
}

char plugboard::getMapping(int index) const
{
    return mapping[index];
}

// If you need to get the entire array (returning pointer)
const char *plugboard::getMappingArray() const
{
    return mapping;
}