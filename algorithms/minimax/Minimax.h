#ifndef MINIMAX_H
#define MINIMAX_H

#include "../../TicTacToe.h"
#include "../../helpers/Tools.h"
#include <limits>
#include <cstdlib>
#include <ctime>

const int MINIMAX_BOARD_SIZE = 3;
const int MINIMAX_POSITIVE_INFINITY = numeric_limits<int>::max();
const int MINIMAX_NEGATIVE_INFINITY = numeric_limits<int>::min();

class Minimax
{
private:
    // PRIVATE ATTRIBUTES
    int player;                 // The player
int enemyPlayer;                // The enemy player 
    TicTacToe (*grid)[3][3];    // Pointer to the nineboard tictactoe.

    // PRIVATE METHODS
    int minimax(TicTacToe *board, const bool isMaximising, const int depth);
    bool isTerminalState(TicTacToe *board, const int depth, int score);
    void simulateMove(TicTacToe *board, const bool isMaximising, const int depth, int &bestScore);

public:
    void useMinimax(int *x, int *y, const Coordinate *currentBoard);

    /**
     * @brief Constructor
     *
     * A simple version of the minimax algorithm. There's no optimisation
     * or criterias on this one. It's simply just a minimax algorithm. This algorithm
     * won't be effective as it thinks to win a single tictactoe game.
     *
     * I added some randomness into this algorithm especially when the board is empty
     * so the algorithm can take advantage of the nine board tictactoe and not get
     * defeated by Random Player all the time.
     *
     * @param grid A pointer to the nineboard tictactoe. Type TicTacToe (*grid)[3][3].
     * @param player The player. Either 1 or -1
     */
    Minimax(TicTacToe (*grid)[3][3], int player)
    {
        srand(time(0));
        this->grid = grid;
        this->player = player;
        this->enemyPlayer = player == 1 ? -1 : 1;
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
void Minimax::useMinimax(int *x, int *y, const Coordinate *currentBoard)
{
    int bestScore = (this->player == -1 ? MINIMAX_NEGATIVE_INFINITY : MINIMAX_POSITIVE_INFINITY);
    int bestX = -1, bestY = -1;

    // Starting board
    TicTacToe *board = &(*grid)[currentBoard->x][currentBoard->y];

    if (!Tools::isBoardEmpty(board))
    {
        // Simulate all possible moevs from the current state of the board
        for (int row = 0; row < MINIMAX_BOARD_SIZE; row++)
        {
            for (int col = 0; col < MINIMAX_BOARD_SIZE; col++)
            {
                // Check if the cell is empty
                if (board->getCell(row, col) == 0)
                {
                    // SIMULATING EACH MOVE
                    // We set the cell to -1 because -1 is computer
                    board->addMove(row, col, this->player);

                    // Determine if player is maximising or minimising.
                    bool isMaximising = (this->player == -1 ? false : true);

                    // Go to the next node (next player).
                    int score = minimax(board, isMaximising, 0);

                    // Undo move
                    board->addMove(row, col, 0);

                    // MAXIMISING
                    if (this->player == -1)
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
int Minimax::minimax(TicTacToe *board, const bool isMaximising, const int depth)
{
    int score = 0;
    if (isTerminalState(board, depth, score)) {
        return score;
    }

    // COMPUTER
    if (isMaximising)
    {
        // We set the initial best score for maximizing player to the lowest possible score. In this case -infinity.
        int bestScore = NEGATIVE_INFINITY;

        // Simulate all possible moves, or generate moves.
        simulateMove(board, isMaximising, depth, bestScore);
        return bestScore;
    }
    // PLAYER
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
bool Minimax::isTerminalState(TicTacToe *board, const int depth, int score)
{
    // Check game status
    int status = board->gameStatus();

    // Check each terminal state
    if (status == 1)            // Minimising player has won
    {
        score = -10 + depth;
        return true;
    }
    else if (status == -1)      // Maximising player has won
    {
        score = 10 - depth;
        return true;
    }
    else if (status == 2)       // Draw
    {
        score = 0;
        return true;
    }

    return false;               // Game is not over
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
    for (int row = 0; row < MINIMAX_BOARD_SIZE; row++)
    {
        for (int col = 0; col < MINIMAX_BOARD_SIZE; col++)
        {
            // Check if the cell is empty on the current selected board
            if (board->getCell(row, col) == 0)
            {
                // Set the cell value to the current player
                board->addMove(row, col, isMaximising ? -1 : 1);

                // Simulate the next move for the next player
                int score = minimax(board, depth + 1, !isMaximising);

                // Undo for the next branch
                board->addMove(row, col, 0);

                // Evaluate the best score
                bestScore = isMaximising ? max(bestScore, score) : min(bestScore, score);
            }
        }
    }
}

#endif