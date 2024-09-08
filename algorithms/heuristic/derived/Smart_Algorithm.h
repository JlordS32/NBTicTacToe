#ifndef SMART_ALGORITHM_H
#define SMART_ALGORITHM_H

#include "../base/Heuristic_Search.h"
#include "../../../struct/Coordinate.h"
#include "../../../TicTacToe.h"

class SmartAlgorithm : public HeuristicSearch
{
public:
    SmartAlgorithm(TicTacToe (*grid)[3][3], int player)
        : HeuristicSearch(grid, player, true)
    {
    }

    void useAlgorithm(int *x, int *y, const Coordinate *currentBoard) override;
};

/**
 * @brief Gets the best move for computer player 'Smart Player'
 *
 * Uses heuristic search algorithm too, but unlike Mindful player, this player
 * will weigh the number of player moves on the coming next board.
 *
 * @param x The x coordinate of the best move
 * @param y The y coordinate of the best move
 * @param currentBoard A pointer to Coordinate struct that holds the position of the current select board for this game.
 */
void SmartAlgorithm::useAlgorithm(int *x, int *y, const Coordinate *currentBoard)
{
    // Initially reset the positions first
    resetPositions();

    // Get the current board
    TicTacToe *board = &(*this->grid)[currentBoard->x][currentBoard->y];

    // SIMULATE ALL MOVES
    checkCentre(board);
    checkCorners(board);
    checkCross(board);

    // ASSIGN THE BEST MOVE TO THE X AND Y POINTERS
    *x = this->bestX;
    *y = this->bestY;
}

#endif
