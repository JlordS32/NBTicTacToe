#ifndef HEURISTIC_SEARCH_H
#define HEURISTIC_SEARCH_H

#include "../../../helpers/Tools.h"
#include "../../base/Algorithm.h"

const int HEURISTIC_MOVE_WEIGHT = 1;
const int HEURISTIC_WIN_WEIGHT = 10;
const int HEURISTIC_INIAL_SCORE = 10;
const int HEURISTIC_NUM_POSITIONS = 4;

class HeuristicSearch : public Algorithm
{
protected:
    // PROTECTED ATTRIBUTES
    int bestScore;
    int bestX;
    int bestY;
    bool weighByEnemyMoves;

    // PROTECTED METHODS
    void resetPositions();
    void checkCentre(TicTacToe *board);
    void checkCorners(TicTacToe *board);
    void checkCross(TicTacToe *board);
    void simulateMove(TicTacToe *board, int arr[HEURISTIC_NUM_POSITIONS][2], int &currScore);
    void evaluateScore(const int currScore, const int x, const int y);
    void weighScore(TicTacToe *nextBoard, int &currScore) const;

public:
    /**
     * @brief Constructor
     *
     * Hueristic approach for finding the best move.
     * This search algorithm simply just looks for centre, corners and cross.
     * It prioritises the following order. Centre > Corners > Cross
     *
     * @param player The player symbol
     * @param grid A pointer to the board
     */
    HeuristicSearch(TicTacToe (*grid)[3][3], int player, bool weighByEnemyMoves = false)
        : Algorithm(grid, player),
          bestScore(-1),
          bestX(-1),
          bestY(-1),
          weighByEnemyMoves(weighByEnemyMoves)
    {
    }

    virtual void useAlgorithm(int *x, int *y, const Coordinate *currentBoard) = 0;
};

/**
 * @brief Resets the positions back to -1
 */
void HeuristicSearch::resetPositions()
{
    this->bestScore = -1;
    this->bestX = -1;
    this->bestY = -1;
}

/**
 * @brief Evaluates the score
 *
 * @param currScore The current score
 * @param x The x coordinate of the best move
 * @param y The y coordinate of the best move
 */
void HeuristicSearch::evaluateScore(const int currScore, const int x, const int y)
{
    if (currScore > this->bestScore)
    {
        this->bestScore = currScore;
        this->bestX = x;
        this->bestY = y;
    }
}

/**
 * @brief Checks if the centre is available and prioritize it
 *
 * @param board A pointer to the board
 */
void HeuristicSearch::checkCentre(TicTacToe *board)
{
    int currScore = HEURISTIC_INIAL_SCORE;

    // Initialise initial coordinates for centre.
    const int centreX = 1, centreY = 1;

    // Check if the centre is available and prioritize it
    if (board->getCell(centreX, centreY) == BOARD_EMPTY)
    {
        if (this->weighByEnemyMoves)
        {
            TicTacToe *nextBoard = &(*grid)[centreX][centreY];

            weighScore(nextBoard, currScore);
        }

        evaluateScore(currScore, centreX, centreY);
    }
}

/**
 * @brief Checks if the cross is available and prioritize it
 *
 * @param board A pointer to the board
 */
void HeuristicSearch::checkCross(TicTacToe *board)
{
    int currScore = HEURISTIC_INIAL_SCORE;

    // Initialise the coordinates for cross position.
    int cross[HEURISTIC_NUM_POSITIONS][2] = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    // Evaluate cross and prioritize the best one
    simulateMove(board, cross, currScore);
}

/**
 * @brief Checks if the corners are available and prioritize them
 *
 * @param board A pointer to the board
 */
void HeuristicSearch::checkCorners(TicTacToe *board)
{
    int currScore = HEURISTIC_INIAL_SCORE;

    // Initialise coordinates for corners.
    int corners[HEURISTIC_NUM_POSITIONS][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};

    // Evaluate corners and prioritize the best one
    simulateMove(board, corners, currScore);
}

/**
 * @brief Generates all possible next move
 *
 * This methods explores all possible next moves and evaluates their score
 * so the algorithm can decide which move is the best.
 *
 * @param board A pointer to the current board.
 * @param arr An array of 4 coordinates. Type int[4][2].
 * @param currScore A reference to the current score.
 */
void HeuristicSearch::simulateMove(TicTacToe *board, int arr[HEURISTIC_NUM_POSITIONS][2], int &currScore)
{
    // Evaluate corners and prioritize the best one
    for (int i = 0; i < HEURISTIC_NUM_POSITIONS; i++)
    {
        // Get the coordinates
        int posX = arr[i][0];
        int posY = arr[i][1];

        if (board->getCell(posX, posY) == BOARD_EMPTY)
        {
            // Simulate the corner move
            board->addMove(posX, posY, this->player);

            // Evaluate the score of the simulated move
            int status = board->gameStatus();

            // We weight the score by the win status
            if (status == this->player)
                currScore += HEURISTIC_WIN_WEIGHT;
            else if (status == this->enemyPlayer)
                currScore -= HEURISTIC_WIN_WEIGHT;

            // Depending if the caller wants to weigh by enemy moves, this statement
            // will be ran.
            if (this->weighByEnemyMoves)
            {
                // Check the number of enemy moves on the next board.
                TicTacToe *nextBoard = &(*grid)[posX][posY];
                weighScore(nextBoard, currScore);
            }

            // Undo the move
            board->addMove(posX, posY, BOARD_EMPTY);

            evaluateScore(currScore, posX, posY);

            // Reset score
            currScore = HEURISTIC_INIAL_SCORE;
        }
    }
}

/**
 * @brief Function to weigh the score of the next board
 *
 * @param nextBoard A pointer to the next board.
 * @param currScore A reference to the current score.
 */
void HeuristicSearch::weighScore(TicTacToe *nextBoard, int &currScore) const
{
    // Check the number of enemy moves on the next board.
    int noOfPlayerMovesNextBoard = Tools::checkValues(nextBoard, this->enemyPlayer);

    // We weight the score by the number of enemy moves.
    currScore -= noOfPlayerMovesNextBoard * HEURISTIC_MOVE_WEIGHT;
}

#endif
