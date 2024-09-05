#ifndef PLAYER_H
#define PLAYER_H

#include "../../TicTacToe.h"
#include "../../struct/Coordinate.h"
#include "../../struct/Move.h"
#include <iostream>
using namespace std;

class Player
{
protected:
    TicTacToe (*grid)[3][3];

public:
    Player(TicTacToe (*grid)[3][3]) {
        this->grid = grid;
    }

    /**
     * @brief Base function for the abstract class Player
     *
     * @param player The player symbol
     * @param x The x value corresponding to the board.
     * @param y The y value corresponding to the board.
     * @param board Takes a pointer to board.
     */
    virtual void getMove(Move *currentPlayer, const Coordinate *currentBoard) = 0;
    virtual string getName() = 0;

    ~Player() {}
};

#endif
