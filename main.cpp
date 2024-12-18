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