#ifndef SMARTPLAYER_H
#define SMARTPLAYER_H

#include "./base/Player.h"
#include "../algorithms/heuristic/derived/Smart_Algorithm.h"
#include "../helpers/Tools.h"

class SmartPlayer : public Player
{
private:
    int player;
    SmartAlgorithm smart;

public:
    SmartPlayer(TicTacToe (*grid)[3][3], int player) : Player(grid), smart(grid, player) {}

    string getName() override;
    void getMove(Move *currentPlayer, const Coordinate *currentBoard) override;

    ~SmartPlayer() {}
};

string SmartPlayer::getName() {
    return "Smart";
}

/**
 * @brief Gets the best move for computer player 'Smart Player'
 *
 * @param x The x coordinate of the best move
 * @param y The y coordinate of the best move
 * @param currentBoard A pointer to Coordinate struct that holds the position of the current select board for this game.
 */
void SmartPlayer::getMove(Move *currentPlayer, const Coordinate *currentBoard)
{
     // Initialise temporary variables to contain the best move.
    int bestX = -1, bestY = -1;

    // Pass it to the heuristic search algorithm.
    smart.useAlgorithm(&bestX, &bestY, currentBoard);

    // ASSIGN THE BEST MOVE TO THE X AND Y POINTERS
    currentPlayer->x = bestX;
    currentPlayer->y = bestY;
}

#endif