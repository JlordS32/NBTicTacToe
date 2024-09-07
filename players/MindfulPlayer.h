#ifndef MINDFULPLAYER_H
#define MINDFULPLAYER_H

#include "./base/Player.h"
#include "../algorithms/heuristic/derived/Mindful_Algorithm.h"
#include "../helpers/Tools.h"

class MindfulPlayer : public Player
{
private:
    int player;
    MindfulAlgorithm mindfulAlgorithm;

public:
    MindfulPlayer(TicTacToe (*grid)[3][3], int player) : Player(grid), mindfulAlgorithm(grid, player) {}

    string getName() override;
    void getMove(Move *currentPlayer, const Coordinate *currentBoard) override; 
};

string MindfulPlayer::getName()
{
    return "Mindful";
}

/**
 * @brief Gets the best move for computer player 'Smart Player'
 *
 * @param x The x coordinate of the best move
 * @param y The y coordinate of the best move
 * @param currentBoard A pointer to Coordinate struct that holds the position of the current select board for this game.
 */
void MindfulPlayer::getMove(Move *currentPlayer, const Coordinate *currentBoard)
{
    // Initialise temporary variables to contain the best move.
    int bestX = -1, bestY = -1;

    // Pass it to the heuristic search algorithm.
    mindfulAlgorithm.useAlgorithm(&bestX, &bestY, currentBoard);

    // ASSIGN THE BEST MOVE TO THE X AND Y POINTERS
    currentPlayer->x = bestX;
    currentPlayer->y = bestY;
}

#endif