#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../../TicTacToe.h"
#include "../../struct/Coordinate.h"

#include <ctime>
#include <cstdlib>

using namespace std;

class Algorithm
{
protected:
    int player;
    int enemyPlayer;
    TicTacToe (*grid)[3][3];

public:
    Algorithm(TicTacToe (*grid)[3][3], int player)
        : grid(grid),
          player(player)
    {
        // Set enemy player
        this->enemyPlayer = player == 1 ? -1 : 1;

        // Seed randomization
        srand(time(0));
    }

    virtual void useAlgorithm(int *x, int *y, const Coordinate *currentBoard) = 0;
};

#endif