#include "enigma_display.cpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
using namespace std;

void print_menu(EnigmaDisplay& display, int currentChoice);

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



void set_plugboard_pair(char plugboard[26], char a, char b, EnigmaDisplay& display) {
    // Get array indices
    int a_idx = a - 'A';
    int b_idx = b - 'A';
    
    // Swap the letters
    plugboard[a_idx] = b;
    plugboard[b_idx] = a;
    
    // Update display
    std::vector<std::pair<char, char> > pairs;
    for(int i = 0; i < 26; i++) {
        if(plugboard[i] != 'A' + i) {
            char x = 'A' + i;
            char y = plugboard[i];
            if(x < y) {
                pairs.push_back(std::make_pair(x, y));
            }
        }
    }
    display.updatePlugboard(pairs);
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
char encrypt_letter(rotor& left, rotor& middle, rotor& right, rotor& reflector, char input, char plugboard[26], EnigmaDisplay& display) {
    cout << "\nEncrypting " << input << endl;
    cout << "Starting positions - Left: " << left.position 
         << " Middle: " << middle.position 
         << " Right: " << right.position << endl;
    
    display.updateRotors(left.normal[0], middle.normal[0], right.normal[0]);
    display.drawFrame();
    
    // 1. First plugboard transformation
    int position = input - 'A';
    char first_swap = plugboard[position];
    position = first_swap - 'A';
    
    // 2. Rotate rotors first (do this before encryption)
    check_and_rotate_rotors(left, middle, right);
    
    cout << "After rotation - Left: " << left.position 
         << " Middle: " << middle.position 
         << " Right: " << right.position << endl;
    
    display.updateRotors(left.normal[0], middle.normal[0], right.normal[0]);
    display.drawFrame();
    
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


string encrypt_message(rotor& left, rotor& middle, rotor& right, rotor& reflector, string message, char plugboard[26], EnigmaDisplay& display) {
    string result = "";
    
    for(int i = 0; i < message.length(); i++) {
        char encrypted_letter = encrypt_letter(left, middle, right, reflector, message[i], plugboard, display);
        result += encrypted_letter;
    }
    
    return result;
}

void print_menu(EnigmaDisplay& display, int currentChoice) {
    display.drawFrame();
    display.displayMenu(currentChoice);
}

int main() {
    // Initialize plugboard
    char plugboard[26];  
    init_plugboard(plugboard);
    
    // Create and initialize all rotors
    rotor right, middle, left, reflector;
    
    // Historical rotor wirings
    char rotor1_config[26] = {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'};
    char rotor2_config[26] = {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H', 'W', 'T', 'M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'};
    char rotor3_config[26] = {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'};
    char reflector_config[26] = {'E', 'J', 'M', 'Z', 'A', 'L', 'Y', 'X', 'V', 'B', 'W', 'F', 'C', 'R', 'Q', 'U', 'O', 'N', 'T', 'S', 'P', 'I', 'K', 'H', 'G', 'D'};

    // Initialize all rotors with default positions
    init_rotor(right, rotor1_config, 'A');
    init_rotor(middle, rotor2_config, 'A');
    init_rotor(left, rotor3_config, 'A');
    init_rotor(reflector, reflector_config);

    EnigmaDisplay display;
    std::vector<std::pair<char, char> > pairs;
    display.updatePlugboard(pairs);

    string message;
    int choice = 1;
    
    
    while(true) {
        print_menu(display, choice);
        
        cin >> choice;
        cin.ignore();

        if(choice == 5) break;

        switch(choice) {
            case 1: {
                cout << "Enter message to encrypt: ";
                getline(cin, message);
                reset_rotors(left, middle, right);
                string result = encrypt_message(left, middle, right, reflector, message, plugboard, display);
                cout << "Encrypted: " << result << endl;
                display.setIO(message, result);  // Changed this line
                display.drawFrame();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
            }
            case 2: {
                cout << "Enter message to decrypt: ";
                getline(cin, message);
                reset_rotors(left, middle, right);
                string result = encrypt_message(left, middle, right, reflector, message, plugboard, display);
                cout << "Decrypted: " << result << endl;
                display.setIO(message, result);  // Changed this line
                display.drawFrame();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
            }
            case 3: {
                cout << "Enter two letters to swap (e.g., AB): ";
                char a, b;
                cin >> a >> b;
                set_plugboard_pair(plugboard, a, b, display);
                string current = "";  // Add this
                string result = string(1, a) + "↔" + string(1, b);  // Add this
                display.setIO(current, result);  // Changed this line
                display.drawFrame();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
            }
            case 4: {
                cout << "Enter three letters for rotor positions (e.g., AAA): ";
                char l, m, r;
                cin >> l >> m >> r;
                init_rotor(left, rotor3_config, l);
                init_rotor(middle, rotor2_config, m);
                init_rotor(right, rotor1_config, r);
                display.updateRotors(left.normal[0], middle.normal[0], right.normal[0]);
                string current = "";  // Add this
                string result = string(1, l) + string(1, m) + string(1, r);  // Add this
                display.setIO(current, result);  // Changed this line
                display.drawFrame();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
            }
        }
    }

    return 0;
}