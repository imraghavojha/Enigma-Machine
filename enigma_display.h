#ifndef ENIGMA_DISPLAY_H
#define ENIGMA_DISPLAY_H

#include <string>
#include <vector>
#include <utility>

class EnigmaDisplay
{
private:
    // State variables
    char rotors[3];
    std::vector<std::pair<char, char>> plugboard_pairs;
    std::string current_input;
    std::string current_output;

    // Display constants
    static const std::string TITLE;
    static const std::string FOOTER;
    static const int MENU_WIDTH;

    // Helper functions
    void clearScreen() const;
    void drawBox(const std::string &title, const std::string &content) const;
    void drawRotorDisplay() const;
    void drawPlugboardDisplay() const;
    void drawIODisplay() const;
    void drawMenuOption(int option, const std::string &text, bool selected) const;

public:
    // Constructor
    EnigmaDisplay();

    // Update functions
    void updateRotors(char left, char middle, char right);
    void updatePlugboard(const std::vector<std::pair<char, char>> &pairs);
    void setIO(const std::string &input, const std::string &output);

    // Display functions
    void drawFrame() const;
    void displayMenu(int currentChoice = 1) const;
    void showMessage(const std::string &message) const;
};

#endif // ENIGMA_DISPLAY_H