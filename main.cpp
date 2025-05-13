#include "enigma_machine.h"
#include "enigma_display.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>
#include <algorithm>

using namespace std;

// Function to convert string to uppercase and filter out non-alphabetic characters
string prepareInput(const string &input)
{
    string result = "";
    for (char c : input)
    {
        if (isalpha(c))
        {
            result += toupper(c);
        }
    }
    return result;
}

// Function to validate menu choice
bool isValidChoice(int choice)
{
    return choice >= 1 && choice <= 5;
}

// Function to animate encryption/decryption
string processMessage(enigma_machine &machine, const string &message,
                      EnigmaDisplay &disp, bool animate = true) // CHANGED: 'display' to 'disp'
{
    string result = "";
    string partial_input = "";
    string partial_output = "";

    for (size_t i = 0; i < message.length(); i++)
    {
        // Build partial strings for display
        partial_input = message.substr(0, i + 1);

        // Encrypt/decrypt the current letter
        char processed = machine.encrypt_letter(message[i]);
        result += processed;
        partial_output = result;

        // Update display
        string positions = machine.get_rotor_positions();
        disp.updateRotors(positions[0], positions[1], positions[2]); // CHANGED: from updateMotors
        disp.setIO(partial_input, partial_output);

        if (animate)
        {
            disp.drawFrame();
            this_thread::sleep_for(chrono::milliseconds(150));
        }
    }

    return result;
}

int main()
{
    // Historical rotor wirings
    char rotor1_config[26] = {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'};
    char rotor2_config[26] = {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H', 'W', 'T', 'M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'};
    char rotor3_config[26] = {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'};
    char reflector_config[26] = {'E', 'J', 'M', 'Z', 'A', 'L', 'Y', 'X', 'V', 'B', 'W', 'F', 'C', 'R', 'Q', 'U', 'O', 'N', 'T', 'S', 'P', 'I', 'K', 'H', 'G', 'D'};

    // Create the enigma machine
    enigma_machine machine(rotor1_config, rotor2_config, rotor3_config, reflector_config);

    // Create the display
    EnigmaDisplay disp; // CHANGED: from 'display' to 'disp'

    // Initialize display
    vector<pair<char, char>> plugboardPairs;
    disp.updatePlugboard(plugboardPairs);
    string positions = machine.get_rotor_positions();
    disp.updateRotors(positions[0], positions[1], positions[2]); // CHANGED: from updateMotors

    int choice = 1;
    bool running = true;

    while (running)
    {
        // Display the current state and menu
        disp.drawFrame();
        disp.displayMenu(choice);

        cout << "\nSelect option (1-5): ";
        cin >> choice;

        if (!isValidChoice(choice))
        {
            disp.showMessage("Invalid choice. Please enter a number between 1 and 5.");
            this_thread::sleep_for(chrono::milliseconds(1500));
            continue;
        }

        cin.ignore(); // Clear the newline character

        switch (choice)
        {
        case 1: // Encrypt message
        case 2:
        { // Decrypt message
            string operation = (choice == 1) ? "encrypt" : "decrypt";
            cout << "Enter message to " << operation << ": ";
            string message;
            getline(cin, message);

            message = prepareInput(message);

            if (message.empty())
            {
                disp.showMessage("Invalid input. Please enter only letters.");
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            }

            // Reset machine and display
            machine.reset_rotors();
            positions = machine.get_rotor_positions();
            disp.updateRotors(positions[0], positions[1], positions[2]); // CHANGED: from updateMotors
            disp.setIO("", "");
            disp.drawFrame();
            disp.showMessage("Processing message...");
            this_thread::sleep_for(chrono::milliseconds(500));

            // Process the message with animation
            string result = processMessage(machine, message, disp, true);

            // Show final result
            disp.setIO(message, result);
            disp.drawFrame();
            disp.showMessage(operation + "ion complete. Result: " + result);

            cout << "\nPress Enter to continue...";
            cin.get();
            break;
        }

        case 3:
        { // Configure plugboard
            cout << "Current plugboard connections: ";
            if (plugboardPairs.empty())
            {
                cout << "None\n";
            }
            else
            {
                for (const auto &pair : plugboardPairs)
                {
                    cout << pair.first << "↔" << pair.second << " ";
                }
                cout << "\n";
            }

            cout << "Enter two letters to connect (or press Enter to skip): ";
            string input;
            getline(cin, input);

            if (input.empty())
            {
                break;
            }

            input = prepareInput(input);

            if (input.length() != 2)
            {
                disp.showMessage("Invalid input. Please enter exactly two letters.");
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            }

            char a = input[0];
            char b = input[1];

            if (a == b)
            {
                disp.showMessage("Cannot connect a letter to itself.");
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            }

            // Check if either letter is already connected
            bool alreadyConnected = false;
            for (const auto &pair : plugboardPairs)
            {
                if (pair.first == a || pair.second == a ||
                    pair.first == b || pair.second == b)
                {
                    alreadyConnected = true;
                    break;
                }
            }

            if (alreadyConnected)
            {
                disp.showMessage("One or both letters are already connected.");
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            }

            // Add the connection
            machine.set_plugboard_pair(a, b);
            plugboardPairs.push_back(make_pair(a, b));
            disp.updatePlugboard(plugboardPairs);

            disp.drawFrame();
            disp.showMessage("Plugboard connection added: " + string(1, a) + "↔" + string(1, b));
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;
        }

        case 4:
        { // Set rotor positions
            cout << "Current rotor positions: " << machine.get_rotor_positions() << "\n";
            cout << "Enter new rotor positions (3 letters, e.g., ABC): ";
            string input;
            getline(cin, input);

            input = prepareInput(input);

            if (input.length() != 3)
            {
                disp.showMessage("Invalid input. Please enter exactly three letters.");
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            }

            // Set new positions
            machine.set_rotor_positions(input[0], input[1], input[2]);
            disp.updateRotors(input[0], input[1], input[2]); // CHANGED: from updateMotors

            disp.drawFrame();
            disp.showMessage("Rotor positions set to: " + input);
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;
        }

        case 5:
        { // Exit
            running = false;
            disp.drawFrame();
            disp.showMessage("Thank you for using the Enigma Machine simulator!");
            this_thread::sleep_for(chrono::milliseconds(1000));
            break;
        }
        }
    }

    return 0;
}