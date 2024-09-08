#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../../TicTacToe.h"
#include "../../struct/Coordinate.h"

#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

// CONSTANTS
const int PLAYER_ONE = 1;
const int PLAYER_TWO = -1;
const int GAME_RUNNING = 0;
const int POSITIVE_INFINITY = std::numeric_limits<int>::max();
const int NEGATIVE_INFINITY = std::numeric_limits<int>::min();
const int BOARD_SIZE = 3;
const int BOARD_EMPTY = 0;
const int BOARD_FULL = 9 * 9;

class Algorithm
{
protected:
    // PRIVATE ATTRIBUTES
    int player;
    int enemyPlayer;
    TicTacToe (*grid)[3][3];

public:
    /**
     * @brief Constructs an Algorithm object with the given grid and player.
     *
     * @param grid The initial grid of the Tic-Tac-Toe game.
     * @param player The player making the moves (-1 or 1).
     */
    Algorithm(TicTacToe (*grid)[3][3], int player)
        : grid(grid),
          player(player)
    {
        // Set enemy player
        this->enemyPlayer = player == 1 ? PLAYER_TWO : PLAYER_ONE;

        // Seed randomization
        srand(time(0));
    }

    virtual void useAlgorithm(int *x, int *y, const Coordinate *currentBoard) = 0;
};

#endif