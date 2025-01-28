#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>

class EnigmaDisplay {
private:
    const std::string TOP_FRAME    = "╔══════[ ENIGMA M3 - TOP SECRET ]══════";
    const std::string BOTTOM_FRAME = "╚══[1940 - WEHRMACHT ENCRYPTION]════";
    
    // Store the current state
    char rotors[3];
    char reflector;
    std::vector<std::pair<char, char> > plugboard_pairs;
    std::string current_input;
    std::string current_output;
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void drawSignalPath() {
    std::cout << "     ┌─[SIGNAL PATH]─------------┐\n";               // Added spacing at start
    std::cout << "     │   IN → R1 → R2 → R3 → REF\n";     // Added spacing at start
    std::cout << "     │   OUT ← R3 ← R2 ← R1 ←\n";        // Added spacing at start
    std::cout << "     └───────────────------------┘\n";               // Added spacing at start
}
    
    void drawRotors(char l, char m, char r) {
        std::cout << "     ┌─[ROTORS]─┐\n";
        std::cout << "     │ III II I │\n";
        std::cout << "     │  " << l << "  " << m << "  " << r << " │\n";
        std::cout << "     └─────────-┘\n";
    }
    
    void drawPlugboard() {
        std::cout << "     ┌─[PLUGBOARD CONNECTIONS]─┐\n";
        std::cout << "     │ ";
        
        for(const auto& pair : plugboard_pairs) {
            std::cout << pair.first << "↔" << pair.second << " ";
        }
        
        for(size_t i = plugboard_pairs.size(); i < 6; i++) {
            std::cout << "    ";  // padding for empty slots
        }
        std::cout << "│\n";
        std::cout << "     └──────────────────────────┘\n";
    }

    void drawIO() {
        std::cout << "\n      [INPUT]:  " << current_input;
        std::cout << "\n      [OUTPUT]: " << current_output << "\n\n";
    }

public:
    EnigmaDisplay() {
        rotors[0] = rotors[1] = rotors[2] = 'A';
        reflector = 'B';
        current_input = "";
        current_output = "";
    }
    
    void updateRotors(char left, char middle, char right) {
        rotors[0] = left;
        rotors[1] = middle;
        rotors[2] = right;
    }
    
    void updatePlugboard(const std::vector<std::pair<char, char> >& pairs) {
        plugboard_pairs = pairs;
    }

    void setIO(const std::string& input, const std::string& output) {
        current_input = input;
        current_output = output;
    }
    
    void drawFrame() {
        clearScreen();
        std::cout << TOP_FRAME << "\n\n";
        
        drawSignalPath();
        std::cout << "\n";
        
        drawRotors(rotors[0], rotors[1], rotors[2]);
        std::cout << "\n";
        
        drawPlugboard();
        drawIO();
        
        std::cout << BOTTOM_FRAME << "\n";
    }
    
    void displayMenu(int currentChoice = 1) {
        std::cout << "\n";
        std::cout << "┌─[SELECT OPERATION]─┐\n";
        std::cout << "│ ┌─────────────────┐\n";
        std::cout << "│ │ " << (currentChoice == 1 ? ">" : " ") << " 1.ENCRYPT    " << (currentChoice == 1 ? "<" : " ") << " │" 
                  << (currentChoice == 1 ? " ACTIVE" : "      ") << "\n";
        std::cout << "│ └─────────────────┘\n";
        std::cout << "│ " << (currentChoice == 2 ? ">" : "|") << " 2.DECRYPT     " << (currentChoice == 2 ? "<" : "|") << " \n";
        std::cout << "│ " << (currentChoice == 3 ? ">" : "|") << " 3.PLUGBOARD   " << (currentChoice == 3 ? "<" : "|") << " \n";
        std::cout << "│ " << (currentChoice == 4 ? ">" : "|") << " 4.ROTORS      " << (currentChoice == 4 ? "<" : "|") << " \n";
        std::cout << "│ " << (currentChoice == 5 ? ">" : "|") << " 5.EXIT        " << (currentChoice == 5 ? "<" : "|") << " \n";
        std::cout << "└─────────────────┘\n";
    }
};