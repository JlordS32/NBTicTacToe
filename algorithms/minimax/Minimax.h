#ifndef MINIMAX_H
#define MINIMAX_H

#include "../../TicTacToe.h"
#include "../../helpers/Tools.h"
#include "../../struct/Coordinate.h"
#include "../base/Algorithm.h"
#include <limits>
#include <cstdlib>
#include <ctime>

const int MINIMAX_MAX_PLAYER = -1;
const int MINIMAX_MIN_PLAYER = 1;
const int MINIMAX_PLAYER_WIN_WEIGHT = 20;

class Minimax : public Algorithm
{
private:
    // PRIVATE METHODS
    int minimax(TicTacToe *board, TicTacToe *nextBoard, const bool isMaximising, const int depth);
    bool isTerminalState(TicTacToe *board, TicTacToe *nextBoard, const int depth, int &score);
    void simulateMove(TicTacToe *board, const bool isMaximising, const int depth, int &bestScore);

public:
    void useAlgorithm(int *x, int *y, const Coordinate *currentBoard);

    /**
     * @brief Constructor
     *
     * A simple version of the minimax algorithm. There's no optimisation,
     * It's simply just a minimax algorithm. This algorithm
     * won't be effective as it thinks to win a single tictactoe game. To prevent from choosing
     * the same first move every time. I gave the this algorithm the ability to check the next board
     * so it can weigh the score of move it'll choose, effectively making it a good model for 
     * nine board tictactoe.
     *
     * @param grid A pointer to the nineboard tictactoe. Type TicTacToe (*grid)[3][3].
     * @param player The player. Either 1 or -1
     */
    Minimax(TicTacToe (*grid)[3][3], int player)
        : Algorithm(grid, player)
    {
    }
};

/**
 * @brief Uses the minimax algorithm that's been implemented to this function.
 *
 * All parameters in this function takes a pointer.
 *
 * @param board Takes a pointer to a board.
 * @param x The x value corresponding to the board. The row.
 * @param y The y value corresponding to the board. To column.
 */
void Minimax::useAlgorithm(int *x, int *y, const Coordinate *currentBoard)
{
    int bestScore = (this->player == MINIMAX_MAX_PLAYER ? NEGATIVE_INFINITY : POSITIVE_INFINITY);
    int bestX = -1, bestY = -1;

    // Starting board
    TicTacToe *board = &(*grid)[currentBoard->x][currentBoard->y];

    // Only simulate if the board is not empty
    if (!Tools::isBoardEmpty(board))
    {
        // Simulate all possible moves from the current state of the board
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                // Check if the cell is empty
                if (board->getCell(row, col) == BOARD_EMPTY)
                {
                    // SIMULATING EACH MOVE
                    // We set the cell to player value = computer.
                    board->addMove(row, col, this->player);

                    // Determine if player is maximising or minimising.
                    bool isMaximising = (this->player == MINIMAX_MAX_PLAYER ? false : true);

                    // Check next board
                    TicTacToe *nextBoard = &(*this->grid)[row][col];

                    // Go to the next node (next player).
                    int score = minimax(board, nextBoard, isMaximising, 0);

                    // Undo move
                    board->addMove(row, col, BOARD_EMPTY);

                    // MAXIMISING
                    if (this->player == MINIMAX_MAX_PLAYER)
                    {
                        if (score > bestScore)
                        {
                            bestScore = score;
                            bestX = row;
                            bestY = col;
                        }
                    }
                    // MINIMISING
                    else
                    {
                        if (score < bestScore)
                        {
                            bestScore = score;
                            bestX = row;
                            bestY = col;
                        }
                    }
                }
            }
        }
    }

    // Choose a random move if the board the player is in is empty.
    else
    {
        Tools::generateRandomMove(&bestX, &bestY);
    }

    // Set the best move
    *x = bestX;
    *y = bestY;
}

/**
 * @brief The minimax algorithm
 *
 * @param board The game board
 * @param depth The depth of the search, also equal to number of moves
 * @param isMaximising Whether it is the computer's turn or not
 * @return The score of the best move
 */
int Minimax::minimax(TicTacToe *board, TicTacToe *nextBoard, const bool isMaximising, const int depth)
{
    int score = 0;
    if (isTerminalState(board, nextBoard, depth, score))
    {
        return score;
    }

    if (isMaximising)
    {
        // We set the initial best score for maximizing player to the lowest possible score. In this case -infinity.
        int bestScore = NEGATIVE_INFINITY;

        // Simulate all possible moves, or generate moves.
        simulateMove(board, isMaximising, depth, bestScore);
        return bestScore;
    }
    else
    {
        // We set the initial best score for minimizing player to the highest possible score. In this case +infinity.
        int bestScore = POSITIVE_INFINITY;

        // Simulate all possible moves
        simulateMove(board, isMaximising, depth, bestScore);
        return bestScore;
    }
}

/**
 * @brief Checks if the game is over
 *
 * TERMINAL STATE
 * Return the score depending on the depth (no of moves)
 * Maximizing player: Better score the closer to 10
 * Minimizing player: Better score the closer to -10
 *
 * @param board The game board
 * @param depth The depth of the search
 * @param score The score of the game
 * @return `true` if the game is over or
 * @return `false` if the game is not over
 */
bool Minimax::isTerminalState(TicTacToe *board, TicTacToe *nextBoard, const int depth, int &score)
{
    // Check game status
    int status = board->gameStatus();

    // Count number of enemy occurrences on the next board.
    int noEnemyOccurrences = Tools::checkValues(nextBoard, this->enemyPlayer);

    // Check each terminal state
    if (status == MINIMAX_MIN_PLAYER) // Minimising player has won
    {
        score = -MINIMAX_PLAYER_WIN_WEIGHT + depth + noEnemyOccurrences;
        return true;
    }
    else if (status == MINIMAX_MAX_PLAYER) // Maximising player has won
    {
        score = MINIMAX_PLAYER_WIN_WEIGHT - (depth + noEnemyOccurrences);
        return true;
    }
    else if (status == GAME_DRAW) // Draw
    {
        score = 0 - noEnemyOccurrences;
        return true;
    }

    return false; // Game is not over
}

/**
 * @brief Simulates all possible moves
 *
 * @param isMaximising Whether it is the computer's turn or not
 * @param board The game board
 * @param bestScore The best score
 * @param depth The depth of the search
 */
void Minimax::simulateMove(TicTacToe *board, const bool isMaximising, const int depth, int &bestScore)
{
    // Simulate all possible moves
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            // Check if the cell is empty on the current selected board
            if (board->getCell(row, col) == BOARD_EMPTY)
            {
                // Set the cell value to the current player
                board->addMove(row, col, isMaximising ? -1 : 1);

                // Check next board
                TicTacToe *nextBoard = &(*this->grid)[row][col];

                // Simulate the next move for the next player
                int score = minimax(board, nextBoard, depth + 1, !isMaximising);

                // Undo for the next branch
                board->addMove(row, col, BOARD_EMPTY);

                // Evaluate the best score
                bestScore = isMaximising ? std::max(bestScore, score) : std::min(bestScore, score);
            }
        }
    }
}

#endif
