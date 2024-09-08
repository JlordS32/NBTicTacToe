#ifndef ADVANCED_IMPROVED_H
#define ADVANCED_IMPROVED_H

#include "../../TicTacToe.h"
#include "../base/Algorithm.h"
#include "../../struct/Coordinate.h"
#include <limits>

// CONSTANTS
const int ADVANCED_MINIMAX_WIN_WEIGHT = 20;
const int ADVANCED_MINIMAX_DRAW_WEIGHT = 0;

// Note: Increasing the depth limit will increase the time complexity for this algorithm.
// There's about 81! possible moves, and calculating that is realistically unfeasible.
const int DEFAULT_DEPTH_LIMIT = 7;
const int ADVANCED_MINIMAX_MAX_DEPTH_LIMIT = 12;

using namespace std;

class Advanced_Minimax : public Algorithm
{
private:
    // PRIVATE ATTRIBUTES
    static int minimaxCalls;
    int depthLimit;

    // PRIVATE METHODS
    int minimax(TicTacToe *prevBoard, TicTacToe *currBoard, bool isMaximising, int depth, int alpha, int beta);
    bool isTerminalState(TicTacToe *prevBoard, TicTacToe *currBoard, int depth, int &score);
    void simulateMove(TicTacToe *currBoard, bool isMaximising, int depth, int alpha, int beta, int &bestScore);
    int getTotalMoves();

public:
    void useAlgorithm(int *x, int *y, const Coordinate *currentBoard);

    /**
     * @brief Constructor
     *
     * Unlike the typical minimax algorithm.
     * This version is improved by limiting depth search and introducing alpha and beta pruning.
     *
     * @param grid A pointer to the nineboard tictactoe. Type TicTacToe (*grid)[3][3].
     * @param player The player. Either 1 or -1
     */
    Advanced_Minimax(TicTacToe (*grid)[3][3], int player, int depthLimit = DEFAULT_DEPTH_LIMIT)
        : Algorithm(grid, player),
          depthLimit(depthLimit)
    {
    }
};

// Static member redefinition
int Advanced_Minimax::minimaxCalls = 0;

/**
 * @brief Use this function to utilise the minimax algorithm for NineBoard TicTacToe game.
 *
 * @param x A pointer x value corresponding to the board.
 * @param y A pointer y value corresponding to the board.
 * @param currentBoard A pointer to Coordinate struct that holds the position of the current select board for this game.
 */
void Advanced_Minimax::useAlgorithm(int *x, int *y, const Coordinate *currentBoard)
{
    // Update how many times this function has been called.
    this->minimaxCalls++;

    //                       WARNING!
    // ----------------------------------------------------
    // The depth must not be greater than 12. This is because
    // Anything over 12 will take too much time to calculate.
    if (depthLimit >= (ADVANCED_MINIMAX_MAX_DEPTH_LIMIT - 3) && this->minimaxCalls < 5)
    {
        cout << "Depth limit too high. Must be less than "
             << ADVANCED_MINIMAX_MAX_DEPTH_LIMIT
             << endl;
        cout << "Computer is thinking..."
             << endl
             << endl;
    }

    // Player -1 will be maximising. It will prioritise the highest score.
    // Player 1 will be minimising. It will prioritise the least score.
    // We initially set the values to either -infinity (maximising) or +infinity (minimising) in respect to the player.
    int bestScore = (this->player == -1 ? NEGATIVE_INFINITY : POSITIVE_INFINITY);
    int bestX = -1, bestY = -1;

    // Starting board
    TicTacToe *board = &(*grid)[currentBoard->x][currentBoard->y];

    // Root nodes
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (board->getCell(row, col) == BOARD_EMPTY)
            {
                // Simulate the move
                board->addMove(row, col, this->player);
                // Get the next board.
                TicTacToe *nextBoard = &(*this->grid)[row][col];

                // Determine if player is maximising or minimising.
                bool isMaximising = (this->player == -1 ? false : true);

                // Initialise the alpha and beta values
                int alpha = NEGATIVE_INFINITY;
                int beta = POSITIVE_INFINITY;

                // Get the score by simulating the next board.
                // This will be the root node. There will be about up to 9 root nodes. Each node will simulate a move and pick the best one.
                int score = minimax(board, nextBoard, isMaximising, 0, alpha, beta);

                // Undo the move
                board->addMove(row, col, BOARD_EMPTY);

                // Depending on the kind of player is our Minimax algorith (1 or -1)
                // The best move is the one that maximises or minimises the score.
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

    // Assign the best move to our pointer variables.
    *x = bestX;
    *y = bestY;
}

/**
 * @brief Minimax algorithm with alpha-beta pruning and depth limit.
 *
 * This algorithm is used to evaluate potential moves depending on the game state,
 * by recursively exploring all possible states up to a specified depth limit (defined by ADVANCED_MINIMAX_DEPTH_LIMIT). Alpha and beta values are used for pruning, to eliminate
 * branches that do not need to be explored as they cannot influence the outcome of the game.
 *
 * @param prevBoard A pointer to the previous TicTacToe board.
 * @param currBoard A pointer to the current TicTacToe board being evaluated.
 * @param isMaximising A boolean indicating whether the current move is for the maximizing player.
 * @param depth The current depth of the recursive tree, used to limit search depth.
 * @return An integer representing the evaluated score of the current board state.
 */
int Advanced_Minimax::minimax(TicTacToe *prevBoard, TicTacToe *currBoard, bool isMaximising, int depth, int alpha, int beta)
{
    // TERMINAL STATE
    // --------------
    int score = 0;
    if (isTerminalState(prevBoard, currBoard, depth, score))
    {
        return score;
    }

    // SIMULATE MOVES
    // --------------
    // Simulate all possible moves and evaluate them.
    if (isMaximising)
    {
        int bestScore = NEGATIVE_INFINITY;
        simulateMove(currBoard, isMaximising, depth, alpha, beta, bestScore);
        return bestScore;
    }
    else
    {
        int bestScore = POSITIVE_INFINITY;
        simulateMove(currBoard, isMaximising, depth, alpha, beta, bestScore);
        return bestScore;
    }
}

/**
 * @brief Checks if the game is over.
 *
 * This function evaluates if the current board state meets any terminal conditions that
 * should end the recursion in the minimax algorithm. It also sets the score based on the
 * terminal state.
 *
 * @param prevBoard A pointer to the previous TicTacToe board.
 * @param currBoard A pointer to the current TicTacToe board being evaluated.
 * @param depth The current depth of the recursive search tree.
 * @param score A reference to an integer where the score for the terminal state will be set.
 * @return `true` if the current state is a terminal state, `false` otherwise.
 *
 * Terminal states include:
 * 1. The minimizing player has won.
 * 2. The maximizing player has won.
 * 3. The previous board is full and was a draw, meaning no more moves can be made.
 * 4. The game is a draw and no more moves can be made.
 * 5. The depth limit of the search tree has been reached.
 */
bool Advanced_Minimax::isTerminalState(TicTacToe *prevBoard, TicTacToe *currBoard, int depth, int &score)
{
    // Get status on the previous board to check if it is a terminal state.
    int prevBoardStatus = prevBoard->gameStatus();

    // Get the number of enemy occurrences to weigh the score.
    int noEnemyOccurrences = Tools::checkValues(currBoard, 1);

    // Check each terminal state.
    if (prevBoardStatus == -1)
    {
        score = ADVANCED_MINIMAX_WIN_WEIGHT - (depth + noEnemyOccurrences);
        return true;
    }
    if (prevBoardStatus == 1)
    {
        score = -ADVANCED_MINIMAX_WIN_WEIGHT + depth + noEnemyOccurrences;
        return true;
    }
    if (prevBoardStatus == 2)
    {
        score = 0;
        return true;
    }
    if (getTotalMoves() == BOARD_FULL)
    {
        score = ADVANCED_MINIMAX_DRAW_WEIGHT - noEnemyOccurrences;
        return true;
    }
    if (depth >= this->depthLimit)
    {
        score = ADVANCED_MINIMAX_DRAW_WEIGHT - noEnemyOccurrences;
        return true;
    }

    return false;
}

/**
 * @brief Move simulator/generator for the minimax algorithm.
 *
 * It takes an array of 4 coordinates and evaluates the score of each move.
 *
 * @param currBoard A pointer to the current board.
 * @param isMaximising A boolean indicating whether the current move is for the maximizing player.
 * @param depth The current depth of the recursive tree, used to limit search depth.
 * @param bestScore A reference to the current best score.
 * @return An integer representing the evaluated score of the current board state.
 */
void Advanced_Minimax::simulateMove(TicTacToe *currBoard, bool isMaximising, int depth, int alpha, int beta, int &bestScore)
{
    // Simulate all possible moves
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            // We can only simulate to positions that are empty.
            if (currBoard->getCell(row, col) == BOARD_EMPTY)
            {
                // Determine player and start move simulation.
                int currPlayer = isMaximising ? -1 : 1;
                currBoard->addMove(row, col, currPlayer);

                TicTacToe *nextBoard = &(*this->grid)[row][col];

                // Go to the next player and pass the next board.
                int score = minimax(currBoard, nextBoard, !isMaximising, depth + 1, alpha, beta);

                // Undo the move. VERY IMPORTANT!
                currBoard->addMove(row, col, BOARD_EMPTY);

                // Update best score and perform the pruning
                if (isMaximising)
                {
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, score);
                }
                else
                {
                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, score);
                }

                // Pruning branches
                if (beta <= alpha)
                {
                    // No need to evaluate further as the outcome is already determined
                    return;
                }
            }
        }
    }
}

/**
 * @brief Get the total number of moves in the game.
 *
 * Use this function to get the total moves of all boards in the nineboard grid.
 *
 * @return An integer representing the total number of moves.
 */
int Advanced_Minimax::getTotalMoves()
{
    int totalMoves = 0;

    // Loop through each individual boards in the grid.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            TicTacToe *board = &(*grid)[i][j];
            totalMoves += board->getNoOfMoves();
        }
    }

    return totalMoves;
}

#endif