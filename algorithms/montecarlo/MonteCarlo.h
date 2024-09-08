#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "../../TicTacToe.h"
#include "../../struct/Coordinate.h"
#include "../base/Algorithm.h"

#include <limits>

using namespace std;

const int MONTE_RUNNING = 0;

class MonteCarlo : public Algorithm
{
private:
    int numSimulations;

    // PRIVATE METHODS
    void simulateMove(TicTacToe *tempBoard, int &tempPlayer, int &status);
    void switchBoard(Coordinate *tempCoords, int x, int y);
    void copyBoard(TicTacToe (*tempGrid)[3][3]);

public:
    MonteCarlo(TicTacToe (*grid)[3][3], int player, int numSimulations = 1000)
        : Algorithm(grid, player),
          numSimulations(numSimulations)
    {
    }

    void useAlgorithm(int *x, int *y, const Coordinate *currentBoard);
};

void MonteCarlo::useAlgorithm(int *x, int *y, const Coordinate *currentBoard)
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
                // Initialize counter for total wins
                int totalWins = 0;

                // Start simulation
                for (int i = 0; i < this->numSimulations; i++)
                {
                    // Create a temporary copy of the grid
                    TicTacToe tempGrid[3][3];
                    Coordinate tempCoords = *currentBoard;

                    // Copy the current board
                    copyBoard(&tempGrid);

                    // Get the first board
                    TicTacToe *tempBoard = &tempGrid[tempCoords.x][tempCoords.y];

                    // Get a reference to the current board in tempGrid
                    tempBoard->addMove(moveX, moveY, player);

                    // Simulate the game
                    int status = tempBoard->gameStatus();
                    int tempPlayer = player;

                    switchBoard(&tempCoords, moveX, moveY);
                    tempBoard = &tempGrid[tempCoords.x][tempCoords.y];

                    while (status == MONTE_RUNNING) // Keep playing until the game is over
                    {
                        simulateMove(tempBoard, tempPlayer, status);
                        switchBoard(&tempCoords, moveX, moveY);
                        tempBoard = &tempGrid[tempCoords.x][tempCoords.y];
                    }

                    // If the player wins the simulated game, increment totalWins
                    if (status == player)
                    {
                        totalWins++;
                    }
                }

                // If this move has the highest win rate, update the best move
                if (totalWins > bestScore)
                {
                    bestScore = totalWins;
                    bestMoveX = moveX;
                    bestMoveY = moveY;
                }
            }
        }
    }

    // Return the best move found
    *x = bestMoveX;
    *y = bestMoveY;
}

void MonteCarlo::simulateMove(TicTacToe *tempBoard, int &tempPlayer, int &status)
{
    // Switch the player
    tempPlayer = (tempPlayer == player) ? enemyPlayer : player;

    // Generate a random move
    int randX, randY;
    do
    {
        randX = rand() % 3;
        randY = rand() % 3;
    } while (tempBoard->getCell(randX, randY) != 0);

    tempBoard->addMove(randX, randY, tempPlayer);

    status = tempBoard->gameStatus();
}

void MonteCarlo::switchBoard(Coordinate *tempCoords, int x, int y)
{
    tempCoords->x = x;
    tempCoords->y = y;
}

void MonteCarlo::copyBoard(TicTacToe (*tempGrid)[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            (*tempGrid)[row][col] = (*this->grid)[row][col];
        }
    }
}

#endif
