// File: plugboard.h
#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class plugboard
{
private:
    char mapping[26];

public:
    // Constructor
    plugboard();

    // Methods
    void set_plugboard_pair(char a, char b);
    char getMapping(char input) const;
    char getMapping(int index) const;
    const char *getMappingArray() const;
};

#endif // PLUGBOARD_H