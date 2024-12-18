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

Step-by-Step Journey of a Letter ✨
1. Typing a Letter 📝
Real Machine: Press a physical key
My Program:
cppCopychar input = 'A';  // When you type a letter
int position = input - 'A';  // Convert to 0-25
2. Plugboard First! 🔌
Real Machine: Signal goes through a physical plugboard with cables
My Program:
cppCopy// If A is swapped with B, A becomes B before encryption
char swapped = plugboard[position];
3. Through the Rotors! 🎡
Real Machine: Electricity flows through 3 mechanical rotors
My Program:
cppCopy// Right rotor
position = step_through_rotor(right, position);
// Middle rotor
position = step_through_rotor(middle, position);
// Left rotor
position = step_through_rotor(left, position);
4. The Reflector Magic 🪞
Real Machine: Signal hits a reflector and bounces back
My Program:
cppCopy// Reflector sends signal back through a different path
position = step_through_rotor(reflector, position);
5. Back Through the Rotors! ↩️
Real Machine: Signal travels back through rotors in reverse
My Program:
cppCopy// Go back through all rotors in reverse
position = step_through_rotor_reverse(left, position);
position = step_through_rotor_reverse(middle, position);
position = step_through_rotor_reverse(right, position);
6. Plugboard Again! 🔄
Real Machine: Signal goes through plugboard one last time
My Program:
cppCopy// Final swap if letter is in plugboard
char final_letter = plugboard[position];
The Cool Rotor Movement! ⚙️
Real Machine

Right rotor: moves every keypress
Middle rotor: moves when right completes full rotation
Left rotor: moves when middle completes full rotation

My Program
cppCopyvoid check_and_rotate_rotors() {
    if (right.position == 25)  // Right rotor made full turn
        rotate_rotor(middle);
    if (middle.position == 25)  // Middle rotor made full turn
        rotate_rotor(left);
    rotate_rotor(right);  // Right always moves
}
Why This is Super Cool! 🌟

Same Input = Different Output 🎯

Because rotors move, same letter encrypts differently each time!
"AAA" might encrypt to "BKW"


Impossible to Guess 🤔

With different rotor positions and plugboard settings
Millions of possible combinations!


Perfect for Learning 📚

Shows how encryption works
Demonstrates arrays, loops, and functions in C++
Models a real historical device!


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

## How to Use It 💡

### Example 1: Basic Encryption
```
Pick option (1-5): 1
Type your message: HELLO
Encrypted result: LZFBD
```

### Example 2: Using Plugboard
```
Pick option (1-5): 3
Which letters to swap? (like AB): HM
Done! Now H and M will swap places
```

### Example 3: Changing Rotor Positions
```
Pick option (1-5): 4
Enter 3 letters (like AAA): XYZ
Rotors set! This completely changes how it encrypts
```

## Cool Features ⭐
- Type something, encrypt it, then decrypt it - you get the original back!
- Rotors turn differently based on position
- You can set up the machine different ways
- Easy to use menu
- Just like the real thing (but way easier to understand!)

---
Made with 💻 and ☕ by a student learning C++!
