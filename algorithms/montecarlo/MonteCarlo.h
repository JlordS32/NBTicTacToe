#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "../../TicTacToe.h"
#include "../../struct/Coordinate.h"

#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

// CONSTANTS
const int MAX_NUM_SIMULATIONS = 10000;

class MonteCarlo
{
private:
    int player;
    int enemyPlayer;
    int numSimulations;
    TicTacToe (*grid)[3][3];

public:
    MonteCarlo(TicTacToe (*grid)[3][3], int player)
        : grid(grid),
          player(player)
    {
        // Set enemy player
        this->enemyPlayer = player == 1 ? -1 : 1;

        // Seed randomisation
        srand(time(0)); 

        // Get number of simulations
        cout << "You selected Monte Carlo Player: Please enter the number of simulations";
        cout << "Enter number of simulations (1-" << MAX_NUM_SIMULATIONS << "): ";
        while (!(cin >> numSimulations) || numSimulations < 1 || numSimulations > MAX_NUM_SIMULATIONS)
        {
            cout << "Invalid input. Please enter a number between 1 and " << MAX_NUM_SIMULATIONS << ": ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << endl;
    }

    void useMonteCarlo(int *x, int *y, const Coordinate *currentBoard);
};

void MonteCarlo::useMonteCarlo(int *x, int *y, const Coordinate *currentBoard)
{
    int bestScore = std::numeric_limits<int>::min();
    int bestMoveX = -1, bestMoveY = -1;

    // Get the current board
    TicTacToe *board = &(*this->grid)[currentBoard->x][currentBoard->y];

    // Simulate all possible moves in the current state
    for (int moveX = 0; moveX < 3; moveX++)
    {
        for (int moveY = 0; moveY < 3; moveY++)
        {
            // If the cell is empty, simulate the move
            if (board->getCell(moveX, moveY) == 0)
            {
                // Initialise counter for total wins
                int totalWins = 0;

                // Start simulation
                for (int i = 0; i < this->numSimulations; i++)
                {
                    TicTacToe tempBoard = *board;

                    // Make the move for the player
                    tempBoard.addMove(moveX, moveY, player);

                    // Simulate the game
                    int status = tempBoard.gameStatus();
                    int tempPlayer = player;

                    while (status == 0)  // Keep playing until the game is over
                    {
                        // Switch the player
                        tempPlayer = (tempPlayer == player) ? enemyPlayer : player;

                        // Make a random move
                        int randX, randY;
                        do
                        {
                            randX = rand() % 3;
                            randY = rand() % 3;
                        } while (tempBoard.getCell(randX, randY) != 0);

                        tempBoard.addMove(randX, randY, tempPlayer);
                        status = tempBoard.gameStatus();
                    }

                    // If the player wins the simulated game, increment totalWins
                    if (status == player)
                    {
                        totalWins++;
                    }
                }

                // Compute win rate for this move
                double averageWins = static_cast<double>(totalWins) / numSimulations;

                // If this move has the highest win rate, update the best move
                if (averageWins > bestScore)
                {
                    bestScore = averageWins;
                    bestMoveX = moveX;
                    bestMoveY = moveY;
                }
            }
        }
    }

    *x = bestMoveX;
    *y = bestMoveY;
}

#endif
