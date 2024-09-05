#ifndef HEURISTIC_SEARCH_H
#define HEURISTIC_SEARCH_H

#include "../../../helpers/Tools.h"

const int HEURISTIC_MOVE_WEIGHT = 1;
const int HEURISTIC_WIN_WEIGHT = 10;
const int HEURISTIC_INIAL_SCORE = 10;
const int HEURISTIC_NUM_POSITIONS = 4;

class HeuristicSearch
{
protected:
    // PROTECTED ATTRIBUTES
    TicTacToe (*grid)[3][3];
    int player;
    int enemyPlayer;
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
    void evaluateScore(int currScore, int x, int y);

public:
    /**
     * @brief Constructor
     *
     * Hueristic approach for finding the best move.
     * This search algorithm simply just looks for centre, corners and cross.
     * It prioritises the following order. Centre > Corners > Cross
     *
     * However due to the nature of the game, every decision is heavily weighted by the number of enemy moves on the next board. This allows the algorithm to effectively think if making a position at x, y is risky or not.
     *
     * @param player The player symbol
     * @param grid A pointer to the board
     */
    HeuristicSearch(TicTacToe (*grid)[3][3], int player, bool weighByEnemyMoves = false)
    {
        this->player = player;
        this->enemyPlayer = (player == 1) ? -1 : 1;
        this->bestScore = -1;
        this->bestX = -1;
        this->bestY = -1;
        this->grid = grid;
        this->weighByEnemyMoves = weighByEnemyMoves;
    }

    virtual void useAlgorithm(int *x, int *y, const Coordinate *currentBoard) = 0;
};

void HeuristicSearch::resetPositions()
{
    this->bestScore = -1;
    this->bestX = -1;
    this->bestY = -1;
}

void HeuristicSearch::evaluateScore(int currScore, int x, int y)
{
    if (currScore > this->bestScore)
    {
        this->bestScore = currScore;
        this->bestX = x;
        this->bestY = y;
    }
}

void HeuristicSearch::checkCentre(TicTacToe *board)
{
    int currScore = HEURISTIC_INIAL_SCORE;

    // Initialise initial coordinates for centre.
    const int centreX = 1, centreY = 1;

    // Check if the centre is available and prioritize it
    if (board->getCell(centreX, centreY) == 0)
    {
        TicTacToe *nextBoard = &(*grid)[centreX][centreY];
        int playerEnemyMoves = Tools::checkValues(nextBoard, this->enemyPlayer);

        currScore -= HEURISTIC_MOVE_WEIGHT * playerEnemyMoves;

        evaluateScore(currScore, centreX, centreY);
    }
}

void HeuristicSearch::checkCross(TicTacToe *board)
{
    int currScore = HEURISTIC_INIAL_SCORE;

    // Initialise the coordinates for cross position.
    int cross[HEURISTIC_NUM_POSITIONS][2] = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    // Evaluate cross and prioritize the best one
    simulateMove(board, cross, currScore);
}

void HeuristicSearch::checkCorners(TicTacToe *board)
{
    int currScore = HEURISTIC_INIAL_SCORE;

    // Initialise coordinates for corners.
    int corners[HEURISTIC_NUM_POSITIONS][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};

    // Evaluate corners and prioritize the best one
    simulateMove(board, corners, currScore);
}

/**
 * @brief Function simulator for this class
 *
 * It takes an array of 4 coordinates and evaluates the score of each move.
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
        int noOfPlayerMovesNextBoard = 0;
        int posX = arr[i][0];
        int posY = arr[i][1];

        if (board->getCell(posX, posY) == 0)
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

            if (this->weighByEnemyMoves)
            {
                // Check the number of enemy moves on the next board.
                TicTacToe *nextBoard = &(*grid)[posX][posY];
                noOfPlayerMovesNextBoard = Tools::checkValues(nextBoard, this->enemyPlayer);

                // We weight the score by the number of enemy moves.
                currScore -= noOfPlayerMovesNextBoard * HEURISTIC_MOVE_WEIGHT;
            }

            // Undo the move
            board->addMove(posX, posY, 0);

            evaluateScore(currScore, posX, posY);

            // Reset score
            currScore = 10;
        }
    }
}

#endif
