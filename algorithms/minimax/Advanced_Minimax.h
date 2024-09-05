#ifndef ADVANCED_IMPROVED_H
#define ADVANCED_IMPROVED_H

#include "../../TicTacToe.h"
#include <limits>

const int ADVANCED_MINIMAX_BOARD_SIZE = 3;
const int ADVANCED_MINIMAX_WIN_WEIGHT = 20;
const int ADVANCED_MINIMAX_DRAW_WEIGHT = 0;
const int BOARD_EMPTY = 0;
const int POSITIVE_INFINITY = numeric_limits<int>::max();
const int NEGATIVE_INFINITY = numeric_limits<int>::min();
const int ADVANCED_MINIMAX_BOARD_FULL = 9 * 9;

// Note: Increasing the depth limit will increase the time complexity for this algorithm.
// There's about 81! possible moves, and calculating that is realistically unfeasible.
const int ADVANCED_MINIMAX_DEPTH_LIMIT = 9;
const int ADVANCED_MINIMAX_MAX_DEPTH_LIMIT = 12;
class Advanced_Minimax
{
private:
    // PRIVATE ATTRIBUTES
    int player;
    int enemyPlayer;
    TicTacToe (*grid)[3][3];
    static int minimaxCalls;

    // PRIVATE METHODS
    int minimax(TicTacToe *prevBoard, TicTacToe *currBoard, bool isMaximising, int depth, int alpha, int beta);
    int getTotalMoves();
    void simulateMove(TicTacToe *currBoard, bool isMaximising, int depth, int alpha, int beta, int &bestScore);

public:
    void useMinimax(int *x, int *y, const Coordinate *currentBoard);

    /**
     * @brief Constructor
     *
     * Unlike the typical minimax algorithm.
     * This version is improved by limiting depth search and introducing alpha and beta pruning.
     *
     * @param grid A pointer to the nineboard tictactoe. Type TicTacToe (*grid)[3][3].
     * @param player The player. Either 1 or -1
     */
    Advanced_Minimax(TicTacToe (*grid)[3][3], int player)
    {
        this->grid = grid;
        this->player = player;
        this->enemyPlayer = player == 1 ? -1 : 1;
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
void Advanced_Minimax::useMinimax(int *x, int *y, const Coordinate *currentBoard)
{
    // Update how many times this function has been called.
    this->minimaxCalls++;

    //                       WARNING!
    // ----------------------------------------------------
    // The depth must not be greater than 12. This is because
    // Anything over 12 will take too much time to calculate.
    if (ADVANCED_MINIMAX_DEPTH_LIMIT >= ADVANCED_MINIMAX_MAX_DEPTH_LIMIT && this->minimaxCalls < 5)
    {
        cout << "Depth limit too high. Must be less than "
             << ADVANCED_MINIMAX_MAX_DEPTH_LIMIT
             << endl;
        cout << "Computer is thinking..."
             << endl
             << endl;
    }

    // Depending on the kind of player is our Minimax algorithm (1 or -1)
    // The best score will be dependent on the what kind of player.
    // Player 1 (or player O) will be minimising. It will prioritise the least score.
    // Player -1 (or player X) will be maximising. It will prioritise the highest score.
    // We initially set the values to either -infinity or +infinity in respect to the player.
    int bestScore = (this->player == -1 ? NEGATIVE_INFINITY : POSITIVE_INFINITY);
    int bestX = -1, bestY = -1;

    // Starting board
    TicTacToe *board = &(*grid)[currentBoard->x][currentBoard->y];
    for (int row = 0; row < ADVANCED_MINIMAX_BOARD_SIZE; row++)
    {
        for (int col = 0; col < ADVANCED_MINIMAX_BOARD_SIZE; col++)
        {
            if (board->getCell(row, col) == BOARD_EMPTY)
            {
                // Simulate the move
                board->addMove(row, col, this->player);
                board->setNoOfMoves(board->getNoOfMoves() + 1);

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
                board->setNoOfMoves(board->getNoOfMoves() - 1);

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
    // Get status on the previous to check if it is a terminal state.
    int prevBoardStatus = prevBoard->gameStatus();

    // Get the number of enemy occurences. To weigh the score.
    // Best moves will be the ones that have less enemy occurences on the current board.
    int noEnemyOccurences = Tools::checkValues(currBoard, 1);

    // TERMINATE STATE
    // -----------------
    // These are the terminal states to terminate the recursive nature of this algorithm.
    // 1. Minimising player wins
    // 2. Maximising player wins
    // 3. If the previous board is full and was a draw. Terminate all simulations. No simulation is needed
    // for this state since there was only one available position.
    // 4. Game is a draw. No more moves can be made.
    // 5. Depth limit reached. No more moves can be made.
    if (prevBoardStatus == -1)
    {
        return ADVANCED_MINIMAX_WIN_WEIGHT - (depth + noEnemyOccurences);
    }
    if (prevBoardStatus == 1)
    {
        return -ADVANCED_MINIMAX_WIN_WEIGHT + depth + noEnemyOccurences;
    }
    if (prevBoardStatus == 2)
    {
        return 0;
    }
    if (getTotalMoves() == ADVANCED_MINIMAX_BOARD_FULL)
    {
        return ADVANCED_MINIMAX_DRAW_WEIGHT - noEnemyOccurences;
    }
    if (depth >= ADVANCED_MINIMAX_DEPTH_LIMIT)
    {
        return ADVANCED_MINIMAX_DRAW_WEIGHT - noEnemyOccurences;
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
    for (int row = 0; row < ADVANCED_MINIMAX_BOARD_SIZE; row++)
    {
        for (int col = 0; col < ADVANCED_MINIMAX_BOARD_SIZE; col++)
        {
            // We can only simulate to positions that are empty.
            if (currBoard->getCell(row, col) == BOARD_EMPTY)
            {
                // Determine player and start move simulation.
                int currPlayer = isMaximising ? -1 : 1;
                currBoard->addMove(row, col, currPlayer);
                currBoard->setNoOfMoves(currBoard->getNoOfMoves() + 1);

                TicTacToe *nextBoard = &(*this->grid)[row][col];

                // Go to the next player and pass the next board.
                int score = minimax(currBoard, nextBoard, !isMaximising, depth + 1, alpha, beta);

                // Undo the move. VERY IMPORTANT!
                currBoard->addMove(row, col, BOARD_EMPTY);
                currBoard->setNoOfMoves(currBoard->getNoOfMoves() - 1);

                // Update best score and perform the pruning
                if (isMaximising)
                {
                    bestScore = max(bestScore, score);
                    alpha = max(alpha, score);
                }
                else
                {
                    bestScore = min(bestScore, score);
                    beta = min(beta, score);
                }

                // Pruning branches
                if (beta <= alpha)
                {
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
    for (int i = 0; i < ADVANCED_MINIMAX_BOARD_SIZE; i++)
    {
        for (int j = 0; j < ADVANCED_MINIMAX_BOARD_SIZE; j++)
        {
            TicTacToe *board = &(*grid)[i][j];
            totalMoves += board->getNoOfMoves();
        }
    }

    return totalMoves;
}

#endif