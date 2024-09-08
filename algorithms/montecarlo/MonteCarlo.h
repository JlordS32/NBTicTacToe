#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "../../TicTacToe.h"
#include "../../struct/Coordinate.h"
#include "../base/Algorithm.h"

#include <limits>

using namespace std;

class MonteCarlo : public Algorithm
{
private:
    int numSimulations;

    // PRIVATE METHODS
    int simulateMoveForPosition(int moveX, int moveY, const Coordinate *currentBoard);
    int playOutGame(TicTacToe (*tempGrid)[3][3], TicTacToe *tempBoard);
    void simulateMove(TicTacToe *tempBoard, int &tempPlayer, int &status, int &moveX, int &moveY);
    void switchBoard(TicTacToe (*tempGrid)[3][3], TicTacToe **tempBoard, int x, int y);
    void copyBoard(TicTacToe (*tempGrid)[3][3]);

public:
    /**
     * @brief Constructs a MonteCarlo object with the given grid, player, and number of simulations.
     *
     * @param grid The initial grid of the Tic-Tac-Toe game.
     * @param player The player making the moves (0 or 1).
     * @param numSimulations The number of simulations to perform.
     */
    MonteCarlo(TicTacToe (*grid)[3][3], int player, int numSimulations = 1000)
        : Algorithm(grid, player),
          numSimulations(numSimulations)
    {
    }

    void useAlgorithm(int *x, int *y, const Coordinate *currentBoard);
};

/**
 * @brief Determines the best move for the current board state using Monte Carlo simulations.
 *
 * @param x Pointer to store the x-coordinate of the best move.
 * @param y Pointer to store the y-coordinate of the best move.
 * @param currentBoard The current state of the board.
 */
void MonteCarlo::useAlgorithm(int *x, int *y, const Coordinate *currentBoard)
{
    int bestScore = std::numeric_limits<int>::min();
    int bestMoveX = -1, bestMoveY = -1;

    // Get the current board
    TicTacToe *board = &(*this->grid)[currentBoard->x][currentBoard->y];

    // Simulate all possible moves in the current state
    for (int moveX = 0; moveX < BOARD_SIZE; moveX++)
    {
        for (int moveY = 0; moveY < BOARD_SIZE; moveY++)
        {
            // If the cell is empty, simulate the move
            if (board->getCell(moveX, moveY) == 0)
            {
                int totalWins = simulateMoveForPosition(moveX, moveY, currentBoard);

                // Evaluate the move based on the number of wins
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

/**
 * @brief Simulates a move for a given position and returns the total number of wins.
 *
 * @param moveX The x-coordinate of the move to simulate.
 * @param moveY The y-coordinate of the move to simulate.
 * @param currentBoard The current state of the board to be used for simulation.
 * @return The total number of wins for the simulated move.
 */
int MonteCarlo::simulateMoveForPosition(int moveX, int moveY, const Coordinate *currentBoard)
{
    int totalWins = 0;

    for (int i = 0; i < this->numSimulations; i++)
    {
        // Create a temporary copy of the grid
        TicTacToe tempGrid[3][3];

        // Copy the current board
        copyBoard(&tempGrid);

        // Get the first board
        TicTacToe *tempBoard = &tempGrid[currentBoard->x][currentBoard->y];

        // Make the move
        tempBoard->addMove(moveX, moveY, this->player);

        // Initial board switch
        switchBoard(&tempGrid, &tempBoard, moveX, moveY);

        // Simulate the game outcome
        int status = playOutGame(&tempGrid, tempBoard);

        // If the player wins, increment the win count
        if (status == player)
        {
            totalWins++;
        }
    }

    return totalWins;
}

/**
 * @brief Plays out the game from a given board state until completion.
 *
 * @param tempGrid A temporary copy of the grid used for simulation.
 * @param tempBoard The board from which to start the game simulation.
 * @return The final status of the game (win/loss/draw).
 */
int MonteCarlo::playOutGame(TicTacToe (*tempGrid)[3][3], TicTacToe *tempBoard)
{
    // Initial status and the current player
    int status = tempBoard->gameStatus();
    int tempPlayer = player;

    // Start simulation
    while (status == GAME_RUNNING)
    {
        int x, y;

        // Simulate a random move
        simulateMove(tempBoard, tempPlayer, status, x, y);

        // Switch a board if the game is not over.
        if (status == GAME_RUNNING)
        {
            switchBoard(tempGrid, &tempBoard, x, y);
        }
    }

    // Return the game status after simulation
    return status;
}

/**
 * @brief Simulates a random move on the given board and updates the status.
 *
 * @param tempBoard The board to simulate the move on.
 * @param tempPlayer The current player performing the move.
 * @param status The status of the game after the move.
 * @param x The x-coordinate of the move performed.
 * @param y The y-coordinate of the move performed.
 */
void MonteCarlo::simulateMove(TicTacToe *tempBoard, int &tempPlayer, int &status, int &x, int &y)
{
    // Switch the player
    tempPlayer = (tempPlayer == player) ? enemyPlayer : player;

    // Generate a random move while board is not empty.
    int randX, randY;
    do
    {
        Tools::generateRandomMove(&randX, &randY);
    } while (tempBoard->getCell(randX, randY) != 0);

    // Add the random move
    tempBoard->addMove(randX, randY, tempPlayer);

    // Update status
    status = tempBoard->gameStatus();

    // Assign move
    x = randX;
    y = randY;
}

/**
 * @brief Switches the board being played.
 *
 * @param tempGrid The grid containing the updated board states.
 * @param tempBoard A pointer to the board to update.
 * @param x The x-coordinate of the move.
 * @param y The y-coordinate of the move.
 */
void MonteCarlo::switchBoard(TicTacToe (*tempGrid)[3][3], TicTacToe **tempBoard, int x, int y)
{
    // Update the address of tempBoard to point to the new board.
    *tempBoard = &(*tempGrid)[x][y];
}

/**
 * @brief Copies the board passed to the passed temporary grid.
 *
 * @param tempGrid The grid to copy the current board state into.
 */
void MonteCarlo::copyBoard(TicTacToe (*tempGrid)[3][3])
{
    // Check rows and cols
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            // Assign each to the temporary grid
            (*tempGrid)[row][col] = (*this->grid)[row][col];
        }
    }
}

#endif
