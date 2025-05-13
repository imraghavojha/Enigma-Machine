#include "enigma_display.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Define static members
const std::string EnigmaDisplay::TITLE = "ENIGMA M3 CIPHER MACHINE";
const std::string EnigmaDisplay::FOOTER = "1940 - WEHRMACHT ENCRYPTION";
const int EnigmaDisplay::MENU_WIDTH = 20;

// Constructor
EnigmaDisplay::EnigmaDisplay() : current_input(""), current_output("")
{
    rotors[0] = rotors[1] = rotors[2] = 'A';
}

// Clear screen function
void EnigmaDisplay::clearScreen() const
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Draw a simple box with title and content
void EnigmaDisplay::drawBox(const std::string &title, const std::string &content) const
{
    int width = std::max(static_cast<int>(content.length() + 4), 30);

    // Top border
    std::cout << "┌─[" << title << "]";
    for (int i = title.length() + 4; i < width; i++)
    {
        std::cout << "─";
    }
    std::cout << "┐\n";

    // Content
    std::cout << "│ " << std::left << std::setw(width - 3) << content << "│\n";

    // Bottom border
    std::cout << "└";
    for (int i = 0; i < width - 1; i++)
    {
        std::cout << "─";
    }
    std::cout << "┘\n";
}

// Draw rotor display
void EnigmaDisplay::drawRotorDisplay() const
{
    std::stringstream ss;
    ss << "Position: " << rotors[0] << " " << rotors[1] << " " << rotors[2];
    drawBox("ROTOR POSITIONS", ss.str());
}

// Draw plugboard display
void EnigmaDisplay::drawPlugboardDisplay() const
{
    std::stringstream ss;
    if (plugboard_pairs.empty())
    {
        ss << "No connections";
    }
    else
    {
        for (size_t i = 0; i < plugboard_pairs.size(); i++)
        {
            if (i > 0)
                ss << "  ";
            ss << plugboard_pairs[i].first << "↔" << plugboard_pairs[i].second;
        }
    }
    drawBox("PLUGBOARD", ss.str());
}

// Draw input/output display
void EnigmaDisplay::drawIODisplay() const
{
    std::cout << "\n";
    std::cout << "INPUT:  " << (current_input.empty() ? "[none]" : current_input) << "\n";
    std::cout << "OUTPUT: " << (current_output.empty() ? "[none]" : current_output) << "\n";
    std::cout << "\n";
}

// Draw menu option
void EnigmaDisplay::drawMenuOption(int option, const std::string &text, bool selected) const
{
    if (selected)
    {
        std::cout << " ▶ " << option << ". " << std::left << std::setw(12) << text << " ◀\n";
    }
    else
    {
        std::cout << "   " << option << ". " << std::left << std::setw(12) << text << "\n";
    }
}

// Update rotor positions
void EnigmaDisplay::updateRotors(char left, char middle, char right)
{
    rotors[0] = left;
    rotors[1] = middle;
    rotors[2] = right;
}

// Update plugboard connections
void EnigmaDisplay::updatePlugboard(const std::vector<std::pair<char, char>> &pairs)
{
    plugboard_pairs = pairs;
}

// Set input/output display
void EnigmaDisplay::setIO(const std::string &input, const std::string &output)
{
    current_input = input;
    current_output = output;
}

// Draw the main frame
void EnigmaDisplay::drawFrame() const
{
    clearScreen();

    // Title
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "║     " << std::left << std::setw(30) << TITLE << " ║\n";
    std::cout << "╚════════════════════════════════════╝\n\n";

    // Rotor display
    drawRotorDisplay();
    std::cout << "\n";

    // Plugboard display
    drawPlugboardDisplay();

    // Input/Output display
    drawIODisplay();

    // Footer
    std::cout << "─────────────────────────────────────\n";
    std::cout << FOOTER << "\n";
}

// Display the menu
void EnigmaDisplay::displayMenu(int currentChoice) const
{
    std::cout << "\n┌────────────────────┐\n";
    std::cout << "│       MENU         │\n";
    std::cout << "├────────────────────┤\n";

    drawMenuOption(1, "ENCRYPT", currentChoice == 1);
    drawMenuOption(2, "DECRYPT", currentChoice == 2);
    drawMenuOption(3, "PLUGBOARD", currentChoice == 3);
    drawMenuOption(4, "ROTORS", currentChoice == 4);
    drawMenuOption(5, "EXIT", currentChoice == 5);

    std::cout << "└────────────────────┘\n";
}

// Show a message (for errors, status, etc.)
void EnigmaDisplay::showMessage(const std::string &message) const
{
    std::cout << "\n[MESSAGE]: " << message << "\n";
}