#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>

#include "../struct/PlayerSymbol.h"
#include "../managers/SymbolManager.h"

using namespace std;

class Menu
{
private:
    PlayerSymbol *playerSymbol;

public:
    Menu(SymbolManager *symbolManager) : playerSymbol(symbolManager->getPlayerSymbol()) {}

    int displayPlayerSelection(int player);
    void welcomeScreen();
};

void Menu::welcomeScreen()
{
    cout << "\t\t----------------------------------------------" << endl;
    cout << "\t\t\tWelcome to the Tic-Tac-Toe Game!" << endl;
    cout << "\t\t----------------------------------------------" << endl
         << endl;
}

/**
 * @brief Displays the player selection menu and returns the selected combination.
 *
 * Player selection menu:
 *
 * 1. Human Player
 * 2. Minimax Player
 * 3. Random Player
 *
 * @param player The player number. Either 1 or -1.
 * @return The player combination. Either 1, 2 or 3.
 */
int Menu::displayPlayerSelection(int player)
{
    int choice = 0;
    char symbol = (player == 1) ? this->playerSymbol->playerOne : this->playerSymbol->playerTwo;

    // DISPLAY THE PLAYER SELECTION MENU
    // --------------------------------
    cout << "SELECT PLAYER: " << symbol << endl
         << endl;
    cout << "1. Human Player" << endl;
    cout << "2. Minimax Player:" << endl;
    cout << "3. Random Player:" << endl;
    cout << "4. Mindful Player:" << endl;
    cout << "5. Smart Player:" << endl;
    cout << "6. Advanced Minimax Player:" << endl
         << endl;


    // QUERY USER FOR CHOICE
    // ---------------------
    cout << "Enter your choice (1-6): ";

    while(!(cin >> choice) && (choice < 1) || (choice > 6)) {
        cout << "Please enter a number (1-6): ";    // Display input again
        cin.clear();                // Clear previous input
        cin.ignore(1000, '\n');     // Discard previous input
    }

    cout << endl;

    return choice;
}

#endif
