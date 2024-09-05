#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include "./base/Player.h"
#include "../helpers/Tools.h"
#include <cstdlib>
#include <ctime>

/**
 * @class Computer
 * @brief The Computer class
 *
 * This class is used to generate a random move for the computer.
 */
class RandomPlayer : public Player
{
public:
    RandomPlayer(TicTacToe (*grid)[3][3]) : Player(grid)
    {
        srand(time(0));
    };
    
    string getName() override;
    void getMove(Move *currentPlayer, const Coordinate *currentBoard) override;
};

string RandomPlayer::getName() {
    return "Random";
}

/**
 * @brief Generates a random move for the computer
 *
 * @param player The player symbol
 * @param x The x value corresponding to the board.
 * @param y The y value corresponding to the board.
 * @param board Takes a pointer to board.
 */
void RandomPlayer::getMove(Move *currentPlayer, const Coordinate *currentBoard)
{
    TicTacToe *board = &(*this->grid)[currentBoard->x][currentBoard->y];
    bool isValid = true;
    int randomX = 0, randomY = 0;

    // Randomly choose a position such that the choosen position is not occupied.
    do
    {
        Tools::generateRandomMove(&randomX, &randomY);
        isValid = board->isValidMove(randomX, randomY);
    } while (!isValid);

    currentPlayer->x = randomX;
    currentPlayer->y = randomY;
}

#endif