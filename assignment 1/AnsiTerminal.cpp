#include <iostream>
#include <unistd.h>   // For read()
#include <termios.h>  // For terminal control
#include "headers/AnsiTerminal.h"

// Constructor: Configure terminal for non-canonical mode
AnsiTerminal::AnsiTerminal() {
    // Save the original terminal settings
    tcgetattr(STDIN_FILENO, &original_tio);
    struct termios new_tio = original_tio;

    // Disable canonical mode and echo for real-time input reading
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

// Destructor: Restore the terminal settings to original state
AnsiTerminal::~AnsiTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}

// Method to print text at a specified position
void AnsiTerminal::printAt(int row, int col, const std::string &text) {
    std::cout << "\033[" << row << ";" << col << "H"<< text << std::flush;
}

// Method to print text with inverted background at a specified position
void AnsiTerminal::printInvertedAt(int row, int col, const std::string &text) {
    std::cout << "\033[" << row << ";" << col << "H\033[7m"<< text << "\033[0m" << std::flush;
    // \033[7m enables reverse video mode, \033[0m resets to normal
}

// Method to clear the terminal screen
void AnsiTerminal::clearScreen() {
    std::cout << "\033[2J\033[H" << std::flush; // Clear screen and move cursor to home
}

// Method to get a single keystroke from the terminal
char AnsiTerminal::getKeystroke(){
    char ch;
    read(STDIN_FILENO, &ch, 1);  // Read the first character

    // If the character falls within ASCII range for control characters
    // Ctrl+A to Ctrl+Z are 0x01 to 0x1A, mapping to 'a' - '@'
    if (ch >= 1 && ch <= 26) {
        // Map Ctrl+A to Ctrl+Z to a more readable form
        return ch + 'A' - 1;
    }

    return ch;  // Return the character as-is if it's a regular key
}

// Method to handle arrow key sequences, Alt keys, and other special keys
char AnsiTerminal::getSpecialKey() {
    char ch = getKeystroke();

    // If it's an escape character, we might be dealing with an escape sequence
    if (ch == '\033'){
        // Peek at the next character to see if it's an arrow key or Alt key combination
        char next_ch;
        if (read(STDIN_FILENO, &next_ch, 1) == 0) return '\033';  // If no more input, it's just ESC

        // Arrow keys and some function keys produce sequences starting with '[' after '\033'
        if (next_ch == '[') {
            char arrow_key;
            if (read(STDIN_FILENO, &arrow_key, 1) == 1) {
                switch (arrow_key) {
                    case 'A': return 'U'; // Up arrow
                    case 'B': return 'D'; // Down arrow
                    case 'C': return 'R'; // Right arrow
                    case 'D': return 'L'; // Left arrow
                    // Add cases for other keys like Home, End, PgUp, PgDn, if needed
                }
            }
        } else {
            // If it's not an arrow sequence, it could be an Alt+Key combination
            // Return the second character as the key pressed with Alt
            return next_ch | 0x80;  // Set high bit to distinguish Alt
        }
    }

    // If it's a normal character or Ctrl combination, return as-is
    return ch;
}