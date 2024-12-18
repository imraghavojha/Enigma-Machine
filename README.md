# Enigma-Machine
# Enigma Machine Simulator Documentation

## Core Components

### 1. Rotor System
Each rotor consists of two parallel columns:
- Normal column: A-Z in order
- Scrambled column: Historical Enigma rotor wirings

Rotor Wirings:
```
Rotor I:   EKMFLGDQVZNTOWYHXUSPAIBRCJ
Rotor II:  AJDKSIRUXBLHWTMCQGZNPYFVOE
Rotor III: BDFHJLCPRTXVZNYEIWGAKMUSQO
```

### 2. Reflector
Two columns like rotors:
- Normal column: A-Z in order
- Scrambled column: EJMZALYXVBWFCRQUONTSPIKHGD

### 3. Signal Path
1. Input letter enters right rotor
2. Find position in normal column
3. Get letter at same position in scrambled column
4. Find this letter's position in next rotor's normal column
5. Repeat through all rotors
6. At reflector, follow same pattern but reverse direction
7. Signal travels back through rotors using same lookup method

### 4. Rotor Movement
- Right rotor: Rotates one position with every keypress
- Middle rotor: Rotates when right rotor completes full rotation
- Left rotor: Rotates when middle rotor completes full rotation
- Both columns in a rotor rotate together

### 5. Configuration Format
Single line format: `ABC XY ZW`
- ABC: Initial rotor positions (Left, Middle, Right)
- XY ZW: Optional plugboard pairs

## Program Structure

### Data Structures
```cpp
struct Rotor {
    char normal[26];     // Standard alphabet A-Z
    char scrambled[26];  // Historical rotor wiring
    int position;        // Current rotation position
};

struct Enigma {
    Rotor left;
    Rotor middle;
    Rotor right;
    char reflector_normal[26];
    char reflector_scrambled[26];
};
```

### Core Functions Needed
1. `void rotate_rotor(Rotor& rotor)`
   - Rotates both columns of the rotor one position
   - Handles wraparound at position 26

2. `void check_and_rotate_rotors(Enigma& machine)`
   - Handles rotation of all rotors based on rules
   - Called before each letter encryption

3. `char encrypt_letter(Enigma& machine, char input)`
   - Main encryption function
   - Implements full signal path through rotors and reflector

4. `void initialize_machine(Enigma& machine, string config)`
   - Sets up initial rotor positions from config string
   - Initializes rotor wirings with historical patterns

### Input Requirements
- All input must be uppercase letters A-Z
- Invalid characters should be ignored
- Configuration must follow specified format

