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

int main() {
    rotor rotor1;
    char rotor1_config[26] = {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'};

    init_rotor(rotor1, rotor1_config);
    
    for(int i = 0; i < 26; i++) {
        cout << rotor1.scrambled[i] << " ";
    }
    cout << endl;

    return 0;
}