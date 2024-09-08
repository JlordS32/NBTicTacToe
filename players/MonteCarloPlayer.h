#ifndef MONTECARLOPLAYER_H
#define MONTECARLOPLAYER_H

#include "./base/Player.h"
#include "../TicTacToe.h"
#include "../algorithms/montecarlo/MonteCarlo.h"
#include "../struct/Coordinate.h"
#include "../struct/Move.h"

using namespace std;

class MonteCarloPlayer : public Player
{
private:
    int player;
    MonteCarlo carlo;

public:
    MonteCarloPlayer(TicTacToe (*grid)[3][3], int player)
        : Player(grid),
          carlo(grid, player)
    {
    }

    string getName() override;
    void getMove(Move *currentPlayer, const Coordinate *currentBoard) override;
};

string MonteCarloPlayer::getName()
{
    return "Monte Carlo";
}

void MonteCarloPlayer::getMove(Move *currentPlayer, const Coordinate *currentBoard)
{
    cout << "Monte Carlo Move: " << endl;
    // Initialise temporary variables to contain the best move.
    int bestX = 0, bestY = 0;

    carlo.useMonteCarlo(&bestX, &bestY, currentBoard);

    // Assign the best move chosen by the algorithm to the x and y pointers.
    currentPlayer->x = bestX;
    currentPlayer->y = bestY;
}

#endif