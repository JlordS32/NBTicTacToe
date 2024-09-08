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
 * @param player The player number. Either 1 or -1.
 * @return The selected player according from the menu.
 */
int Menu::displayPlayerSelection(int player)
{
    int choice = 0;
    char symbol = (player == 1) ? this->playerSymbol->playerOne : this->playerSymbol->playerTwo;

    string players[] = {"Human", "Random", "Minimax", "Mindful", "Smart", "Monte Carlo", "Advanced Minimax"};
    int totalPlayers = sizeof(players) / sizeof(players[0]);

    // DISPLAY THE PLAYER SELECTION MENU
    // --------------------------------
    cout << "SELECT PLAYER: " << symbol << endl
         << endl;
    for (int i = 0; i < totalPlayers; i++)
    {
        cout << i + 1
             << ". "
             << players[i]
             << " Player"
             << endl;
    }

    cout << endl;
    cout << "0 to choose at random" << endl;
    cout << endl;

    // QUERY USER FOR CHOICE
    // ---------------------
    cout << "Enter your choice (1-" << totalPlayers << "): ";

    while (!(cin >> choice) || (choice < 0) || (choice > totalPlayers))
    {
        cout << "Please enter a number (1-" << totalPlayers << "): ";  // Display input again
        cin.clear();                                                   // Clear previous input
        cin.ignore(1000, '\n');                                        // Discard previous input
    }

    cout << endl;

    // Choose player at random if choice is 0
    if (choice == 0) {
        choice = (rand() % totalPlayers) + 1;
    }

    return choice;
}

#endif
