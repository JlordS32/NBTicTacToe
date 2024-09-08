#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "../TicTacToe.h"
#include "../struct/Coordinate.h"
#include "../struct/Move.h"
#include "./base/Player.h"

using namespace std;

class HumanPlayer : public Player
{
public:
    HumanPlayer(TicTacToe (*grid)[3][3]) : Player(grid) {};

    string getName() override;
    void getMove(Move *currentPlayer, const Coordinate *currentBoard) override;
};

string HumanPlayer::getName() {
    return "Human";
}

/**
 * @brief Gets an input from a user
 *
 * @param player The player symbol
 * @param x The x value corresponding to the board.
 * @param y The y value corresponding to the board.
 * @param board Takes a pointer to board.
 */
void HumanPlayer::getMove(Move *currentPlayer, const Coordinate *currentBoard)
{
    int row, col;

    bool isValid = true;
    TicTacToe *board = &(*this->grid)[currentBoard->x][currentBoard->y];

    do
    {
        // Checking if false, if false display error message.
        if (!isValid)
        {
            cout << "Error: Invalid position! You can only "
                 << "enter a number between 1-3 and the position must be empty!!"
                 << endl
                 << endl;
        }

        // Input for row
        cout << "Enter row position (1-3): ";
        cin >> row;

        // Input for col
        cout << "Enter col position (1-3): ";
        cin >> col;

        cout << endl;

        // Store the validator function into isValid.
        isValid = board->isValidMove(row - 1, col - 1);
    } while (!isValid);

    currentPlayer->x = row - 1;
    currentPlayer->y = col - 1;
}

#endif