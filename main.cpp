#include <iostream>
#include <string>
using namespace std;

struct rotor {
    char normal[26];
    char scrambled[26];
    int position;
    char init_position;
};
void init_plugboard(char plugboard[26]) {
    // Initialize with default mapping (no swaps)
    for(int i = 0; i < 26; i++) {
        plugboard[i] = 'A' + i;
    }
}
void set_plugboard_pair(char plugboard[26], char a, char b) {
    // Get array indices
    int a_idx = a - 'A';
    int b_idx = b - 'A';
    
    // Swap the letters
    plugboard[a_idx] = b;
    plugboard[b_idx] = a;
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
void init_rotor(rotor& x, char config[26], char init_config = 'A') {
    // Initialize normal A-Z array
    for(int i = 0; i < 26; i++) {
        x.normal[i] = 'A' + i;
    }
    // Initialize scrambled array with config
    for(int i = 0; i < 26; i++) {
        x.scrambled[i] = config[i];
    }
    x.position = 0;
    x.init_position = init_config;  // Store initial position

    while(x.normal[0] != x.init_position) {  // Fixed: using init_position
        rotate_rotor(x);
    }
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
    // Reset left rotor
    while(left.normal[0] != left.init_position) {
        rotate_rotor(left);
    }
    
    // Reset middle rotor
    while(middle.normal[0] != middle.init_position) {
        rotate_rotor(middle);
    }
    
    // Reset right rotor
    while(right.normal[0] != right.init_position) {
        rotate_rotor(right);
    }
}
char encrypt_letter(rotor& left, rotor& middle, rotor& right, rotor& reflector, char input, char plugboard[26]) {
    cout << "\nEncrypting " << input << endl;
    cout << "Starting positions - Left: " << left.position 
         << " Middle: " << middle.position 
         << " Right: " << right.position << endl;
    
    // 1. First plugboard transformation
    int position = input - 'A';
    char first_swap = plugboard[position];
    position = first_swap - 'A';
    
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
    
    // 6. Second plugboard transformation
    return plugboard[position];
}
string encrypt_message(rotor& left, rotor& middle, rotor& right, rotor& reflector, string message, char plugboard[26]) {
    string result = "";
    
    for(int i = 0; i < message.length(); i++) {
        char encrypted_letter = encrypt_letter(left, middle, right, reflector, message[i], plugboard);
        result += encrypted_letter;
    }
    
    return result;
}

int main() {
    // Initialize plugboard
    char plugboard[26];  
    init_plugboard(plugboard);
    
    // Set up some test pairs: A<->B, X<->Z
    set_plugboard_pair(plugboard, 'A', 'B');
    set_plugboard_pair(plugboard, 'X', 'Z');
    
    // Create and initialize all rotors
    rotor right, middle, left, reflector;
    
    // Historical rotor wirings
    char rotor1_config[26] = {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'};
    char rotor2_config[26] = {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H', 'W', 'T', 'M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'};
    char rotor3_config[26] = {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'};
    char reflector_config[26] = {'E', 'J', 'M', 'Z', 'A', 'L', 'Y', 'X', 'V', 'B', 'W', 'F', 'C', 'R', 'Q', 'U', 'O', 'N', 'T', 'S', 'P', 'I', 'K', 'H', 'G', 'D'};

    // Initialize all rotors
    init_rotor(right, rotor1_config, 'C');
    init_rotor(middle, rotor2_config);
    init_rotor(left, rotor3_config);
    init_rotor(reflector, reflector_config);

    cout << "\n*** Testing Full Message Encryption ***\n";
    
    // Test message encryption
    string test_message = "HELLO";
    cout << "\nOriginal message: " << test_message << endl;
    
    reset_rotors(left, middle, right);  // Make sure rotors are in initial position
    string encrypted = encrypt_message(left, middle, right, reflector, test_message, plugboard);
    cout << "Encrypted message: " << encrypted << endl;
    
    reset_rotors(left, middle, right);  // Reset before decryption
    string decrypted = encrypt_message(left, middle, right, reflector, encrypted, plugboard);
    cout << "Decrypted message: " << decrypted << endl;

    // Test another message
    test_message = "ENIGMA";
    cout << "\nOriginal message: " << test_message << endl;
    
    reset_rotors(left, middle, right);
    encrypted = encrypt_message(left, middle, right, reflector, test_message, plugboard);
    cout << "Encrypted message: " << encrypted << endl;
    
    reset_rotors(left, middle, right);
    decrypted = encrypt_message(left, middle, right, reflector, encrypted, plugboard);
    cout << "Decrypted message: " << decrypted << endl;

    return 0;
}