#ifndef MINDFUL_ALGORITHM_H
#define MINDFUL_ALGORITHM_H

#include "../../../helpers/Tools.h"
#include "../base/Hueristic_Search.h"
#include <cstdlib>
#include <ctime>

class MindfulAlgorithm : public HeuristicSearch
{
public:
    MindfulAlgorithm(TicTacToe (*grid)[3][3], int player)
        : HeuristicSearch(grid, player)
    {
        // Seed the random number generator.
        srand(time(0));
    }

    void useAlgorithm(int *x, int *y, const Coordinate *currentBoard) override;
};

/**
 * @brief Gets the best move for computer player 'Mindful Player'
 *
 * Uses heuristic search algorithm to find the best move, but the algorithm for this player
 * will not weigh the number of player moves on the coming next board.
 *
 * @param x The x coordinate of the best move
 * @param y The y coordinate of the best move
 * @param currentBoard A pointer to Coordinate struct that holds the position of the current select board for this game.
 */
void MindfulAlgorithm::useAlgorithm(int *x, int *y, const Coordinate *currentBoard)
{
    // Initially reset the positions first
    resetPositions();

    // Get the current board
    TicTacToe *board = &(*this->grid)[currentBoard->x][currentBoard->y];

    // Unless if the board this player is on an empty board.
    // The move will be randomly selected.
    if (!Tools::isBoardEmpty(board))
    {
        // SIMULATE ALL MOVES
        checkCentre(board);
        checkCorners(board);
        checkCross(board);
    }
    else
    {
        // Randomly select a position instead.
        Tools::generateRandomMove(&this->bestX, &this->bestY);
    }

    // ASSIGN THE BEST MOVE TO THE X AND Y POINTERS
    *x = this->bestX;
    *y = this->bestY;
}

#endif
