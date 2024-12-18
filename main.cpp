#include <iostream>
using namespace std;

struct rotor {
    char normal[26];
    char scrambled[26];
    int position;
};

void init_rotor(rotor& x, char config[26]) {
    // Initialize normal A-Z array
    for(int i = 0; i < 26; i++) {
        x.normal[i] = 'A' + i;
    }
    // Initialize scrambled array with config
    for(int i = 0; i < 26; i++) {
        x.scrambled[i] = config[i];
    }
    x.position = 0;
}
void rotate_column(char y[26]) {  
    char first = y[0];
    for(int i = 0; i < 25; i++) {  
        y[i] = y[i + 1];
    }
    y[25] = first;  
}
void rotate_rotor(rotor& x) {
    rotate_column(x.normal);
    rotate_column(x.scrambled);
    x.position = (x.position + 1) % 26;  
}
void check_and_rotate_rotors(rotor& left, rotor& middle, rotor& right) {
    if (right.position == 25) {   // positions are 0-25
        rotate_rotor(middle);    
    } 
    if (middle.position == 25) { 
        rotate_rotor(left);       
    }
    rotate_rotor(right);          // right rotor always rotates
}
int step_through_rotor(rotor& r, int position) {
    // Forward path (right to left)
    char letter = r.scrambled[position];  // Get letter from scrambled at position
    
    // Find this letter's position in next rotor's normal array
    for (int i = 0; i < 26; i++) {
        if (letter == r.normal[i]) {
            return i;
        }
    }
    return -1;
}
int step_through_rotor_reverse(rotor& r, int position) {
    // Reverse path (left to right)
    char letter = r.normal[position];  // Get letter from normal at position
    
    // Find this letter's position in next rotor's scrambled array
    for (int i = 0; i < 26; i++) {
        if (letter == r.scrambled[i]) {
            return i;
        }
    }
    return -1;
}
void reset_rotors(rotor& left, rotor& middle, rotor& right) {
    // Calculate how many rotations needed to get back to 0
    while(right.position != 0) {
        rotate_rotor(right);
    }
    while(middle.position != 0) {
        rotate_rotor(middle);
    }
    while(left.position != 0) {
        rotate_rotor(left);
    }
}

char encrypt_letter(rotor& left, rotor& middle, rotor& right, rotor& reflector, char input) {
    cout << "\nEncrypting " << input << endl;
    cout << "Starting positions - Left: " << left.position 
         << " Middle: " << middle.position 
         << " Right: " << right.position << endl;
    
    // 1. Convert input letter to position (0-25)
    int position = input - 'A';  
    
    // 2. Rotate rotors first (do this before encryption)
    check_and_rotate_rotors(left, middle, right);
    
    cout << "After rotation - Left: " << left.position 
         << " Middle: " << middle.position 
         << " Right: " << right.position << endl;
    
    // 3. Forward path through rotors
    position = step_through_rotor(right, position);
    position = step_through_rotor(middle, position);
    position = step_through_rotor(left, position);
    
    // 4. Through reflector
    position = step_through_rotor(reflector, position);
    
    // 5. Reverse path through rotors
    position = step_through_rotor_reverse(left, position);
    position = step_through_rotor_reverse(middle, position);
    position = step_through_rotor_reverse(right, position);
    
    // 6. Convert final position back to letter
    return 'A' + position;
}

int main() {
    // Create and initialize all rotors
    rotor right, middle, left, reflector;
    
    // Historical rotor wirings
    char rotor1_config[26] = {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'};
    char rotor2_config[26] = {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H', 'W', 'T', 'M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'};
    char rotor3_config[26] = {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'};
    char reflector_config[26] = {'E', 'J', 'M', 'Z', 'A', 'L', 'Y', 'X', 'V', 'B', 'W', 'F', 'C', 'R', 'Q', 'U', 'O', 'N', 'T', 'S', 'P', 'I', 'K', 'H', 'G', 'D'};

    // Initialize all rotors
    init_rotor(right, rotor1_config);
    init_rotor(middle, rotor2_config);
    init_rotor(left, rotor3_config);
    init_rotor(reflector, reflector_config);

    // // Test 1: Multiple letters
    // char test_word[] = "AAAAA";
    // cout << "Input: " << test_word << endl;
    // cout << "Encrypted: ";
    // for(int i = 0; i < 5; i++) {
    //     cout << encrypt_letter(left, middle, right, reflector, test_word[i]);
    // }
    // cout << endl;

    // Test 2: Reciprocal
    char test_char = 'A';
    char encrypted = encrypt_letter(left, middle, right, reflector, test_char);
    reset_rotors(left, middle, right);  // Reset before decrypting
    char decrypted = encrypt_letter(left, middle, right, reflector, encrypted);
    cout << "Original: " << test_char << " -> Encrypted: " << encrypted << " -> Decrypted: " << decrypted << endl;

    return 0;

    
}