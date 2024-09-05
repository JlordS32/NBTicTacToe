#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "./base/Player.h"
#include "../algorithms/minimax/Minimax.h"
#include "../helpers/Tools.h"

/**
 * @class MinimaxPlayer
 * @brief The MinimaxPlayer class
 *
 * This class is used to generate a random move for the smart player.
 */
class MinimaxPlayer : public Player
{
private:
    Minimax minimax;

public:
    MinimaxPlayer(TicTacToe (*grid)[3][3], int player) : Player(grid), minimax(grid, player) {};

    string getName() override;
    void getMove(Move *currentPlayer, const Coordinate *currentBoard) override;

    ~MinimaxPlayer() {}
};

string MinimaxPlayer::getName()
{
    return "Minimax";
}

/**
 * @brief Generates a move for computer using minimax algorithm.
 *
 * @param x The x value corresponding to the board.
 * @param y The y value corresponding to the board.
 * @param currentBoard A pointer to Coordinate struct that holds the position of the current select board for this game.
 */
void MinimaxPlayer::getMove(Move *currentPlayer, const Coordinate *currentBoard)
{
    // Initialise temporary variables to contain the best move.
    int bestX = -1, bestY = -1;

    // Pass it to the minimax algorithm.
    minimax.useMinimax(&bestX, &bestY, currentBoard);

    // Assign the best move to the x and y pointers.
    currentPlayer->x = bestX;
    currentPlayer->y = bestY;
}

#endif