# 🔐 Documentation

The Real Enigma vs My Program 🔄
The Physical Machine 🛠️
Imagine a typewriter with light bulbs for each letter. When you press a key:

Electricity flows through mechanical rotors (spinning wheels with wires)
Each rotor has 26 contacts on each side (one for each letter)
The signal bounces through multiple rotors
Finally lights up a different letter!

My Program Version 💻
I recreated this using arrays and simple logic:

Instead of physical rotors → I use arrays
Instead of electrical signals → I use numbers (0-25 for A-Z)
Instead of mechanical rotation → I shift array positions
Instead of light bulbs → I output characters

## Main Parts of the Program 🛠️

### 1. Rotor System 🎡

Think of rotors like spinning wheels that scramble letters. Each rotor has:

- A normal alphabet (A-Z in order)
- A scrambled alphabet (using real Enigma machine patterns!)
- A position counter (0-25)
- A starting position setting

Here are the actual letter patterns I used (these are real Enigma patterns!):

```
Rotor 1: EKMFLGDQVZNTOWYHXUSPAIBRCJ
Rotor 2: AJDKSIRUXBLHWTMCQGZNPYFVOE
Rotor 3: BDFHJLCPRTXVZNYEIWGAKMUSQO
Reflector: EJMZALYXVBWFCRQUONTSPIKHGD
```

### 2. Plugboard System 🔌

This is like having special rules where you can swap pairs of letters:

- Pick two letters to swap (like A↔B)
- When you type A, it becomes B (and vice versa)
- This happens before and after the main encryption
- Super simple but adds extra security!

### 3. What Can You Do? 🎮

The program has a simple menu with 5 options:

1. Encrypt a message ✍️
2. Decrypt a message 📖
3. Set up plugboard swaps 🔄
4. Change rotor positions 🎲
5. Exit program 👋

### 4. How It's Built 🏗️

Here's the basic structure I used (this is the actual C++ code!):

```cpp
struct rotor {
    char normal[26];     // Regular A-Z
    char scrambled[26];  // Mixed-up version
    int position;        // Where the rotor is (0-25)
    char init_position;  // Where it starts
};
```

## Main Functions 🔧

### Rotor Stuff

1. `rotate_rotor`: Makes the rotor spin one click
2. `init_rotor`: Sets up a new rotor with its scrambled pattern
3. `reset_rotors`: Puts all rotors back to start position

### Encryption Stuff

1. `encrypt_letter`: Handles one letter at a time

   - Runs it through the plugboard
   - Through all the rotors
   - Back through plugboard
   - Super complex but works great!

2. `encrypt_message`: Handles whole messages
   - Uses encrypt_letter for each character
   - Keeps track of rotor positions

### Plugboard Stuff

1. `init_plugboard`: Sets up basic A-Z mapping
2. `set_plugboard_pair`: Lets you swap letter pairs

# Step-by-Step Journey of a Letter Through Enigma 🔍

## 1. Letter Input Stage 📝

When you type a letter, it first gets converted to a number (0-25):

```cpp
char input = 'A';              // User types a letter
int position = input - 'A';    // 'A' becomes 0, 'B' becomes 1, etc.
```

## 2. First Plugboard Transformation 🔌

Before entering rotors, letter might get swapped by plugboard:

```cpp
// If A is connected to B in plugboard:
// position = 0 (for 'A')
char first_swap = plugboard[position];  // Gets 'B'
position = first_swap - 'A';           // New position becomes 1 (for 'B')
```

## 3. Through the Rotor System (Forward Path) ➡️

Signal passes through each rotor from right to left:

```cpp
// Right Rotor
position = step_through_rotor(right, position);
// Goes from position 1 to new position based on rotor wiring

// Middle Rotor
position = step_through_rotor(middle, position);
// Takes previous position to new position

// Left Rotor
position = step_through_rotor(left, position);
// Final forward transformation
```

## 4. Reflector Bounce 🪞

Signal hits reflector and returns on different path:

```cpp
position = step_through_rotor(reflector, position);
// Reflector ensures no letter can encrypt to itself
```

## 5. Return Through Rotors (Reverse Path) ⬅️

Signal travels back through rotors in opposite direction:

```cpp
// Left Rotor (reverse)
position = step_through_rotor_reverse(left, position);

// Middle Rotor (reverse)
position = step_through_rotor_reverse(middle, position);

// Right Rotor (reverse)
position = step_through_rotor_reverse(right, position);
```

## 6. Final Plugboard Pass 🔄

One last transformation through plugboard:

```cpp
// If position represents 'B', and B is connected to A
return plugboard[position];  // Returns 'A'
```

## 7. Rotor Movement Update ⚙️

After each letter, rotors rotate according to rules:

```cpp
void check_and_rotate_rotors(rotor& left, rotor& middle, rotor& right) {
    if (right.position == 25) {    // Right rotor made full turn
        rotate_rotor(middle);
    }
    if (middle.position == 25) {   // Middle rotor made full turn
        rotate_rotor(left);
    }
    rotate_rotor(right);           // Right rotor always rotates
}
```

## Example Complete Path:

```cpp
Input 'A' →
  Position 0 →
    Plugboard (A→B) → Position 1 →
      Right Rotor → Position 14 →
        Middle Rotor → Position 22 →
          Left Rotor → Position 8 →
            Reflector → Position 19 →
          Left Rotor reverse → Position 11 →
        Middle Rotor reverse → Position 4 →
      Right Rotor reverse → Position 7 →
    Plugboard →
Output 'H'
```

Each step changes the letter's path, and because rotors move after each letter, the same input letter will encrypt differently next time! 🎯

- Just like the real thing (but way easier to understand!)

---

Made with 💻 and ☕ by a student learning C++!
