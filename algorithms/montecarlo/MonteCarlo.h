#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "../../TicTacToe.h"
#include "../../struct/Coordinate.h"

#include <ctime>
#include <cstdlib>
#include <limits>

using namespace  std;

class MonteCarlo
{
public:
    void useMonteCarlo(int *x, int *y, const Coordinate *currentBoard);
};

void MonteCarlo::useMonteCarlo(int *x, int *y, const Coordinate *currentBoard)
{
    // if (noOfMoves >= 9)
    //     return false;

    // srand(static_cast<unsigned int>(time(0)));

    // int num_simulations = 1000;
    // int bestScore = numeric_limits<int>::min();
    // int bestMoveX = -1, bestMoveY = -1;
    // int currPlayer = -1; // Computer's player
    // int enemyPlayer = 1;

    // for (int moveX = 0; moveX < 3; moveX++)
    // {
    //     for (int moveY = 0; moveY < 3; moveY++)
    //     {
    //         if (board[moveX][moveY] == 0)
    //         {
    //             int totalWins = 0;

    //             for (int i = 0; i < num_simulations; i++)
    //             {
    //                 int tempBoard[3][3];
    //                 int tempNoOfMoves = noOfMoves;
    //                 int player = currPlayer;
    //                 bool gameOver = false;

    //                 // Copy the board
    //                 for (int r = 0; r < 3; r++)
    //                 {
    //                     for (int c = 0; c < 3; c++)
    //                     {
    //                         tempBoard[r][c] = board[r][c];
    //                     }
    //                 }

    //                 // Make the move
    //                 tempBoard[moveX][moveY] = player;
    //                 tempNoOfMoves++;

    //                 // Simulate the game
    //                 int status = gameStatus(tempBoard, tempNoOfMoves);

    //                 while (!gameOver && tempNoOfMoves < 9)
    //                 {
    //                     // Switch player
    //                     player = (player == currPlayer) ? enemyPlayer : currPlayer;

    //                     // Random move for the opponent
    //                     int oppX, oppY;
    //                     do
    //                     {
    //                         oppX = rand() % 3;
    //                         oppY = rand() % 3;
    //                     } while (tempBoard[oppX][oppY] != 0);

    //                     tempBoard[oppX][oppY] = player;
    //                     tempNoOfMoves++;

    //                     // Check for game status
    //                     status = gameStatus(tempBoard, tempNoOfMoves);
    //                     if (status == currPlayer)
    //                     {
    //                         totalWins++;
    //                     }
    //                     else if (status != 0) // If game ends with a draw or loss
    //                     {
    //                         gameOver = true;
    //                     }
    //                 }
    //             }

    //             // Compute average win rate for this move
    //             double averageWins = totalWins / num_simulations;

    //             // Update best move if this move is better
    //             if (averageWins > bestScore)
    //             {
    //                 bestScore = averageWins;
    //                 bestMoveX = moveX;
    //                 bestMoveY = moveY;
    //             }
    //         }
    //     }
    // }

    // x = bestMoveX;
    // y = bestMoveY;
}

#endif