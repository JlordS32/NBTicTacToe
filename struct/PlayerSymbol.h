#ifndef PLAYERSYMBOL_H
#define PLAYERSYMBOL_H

#include "../helpers/Tools.h"

const char DEFAULT_PLAYER_SYMBOL[2] = {'X', 'O'};

/**
 * @brief A simple struct to store the coordinates of the nineboard grid.
 */
struct PlayerSymbol
{
    char playerOne;
    char playerTwo;
    char emptySymbol;

    PlayerSymbol() {
        this->playerOne = DEFAULT_PLAYER_SYMBOL[0];
        this->playerTwo = DEFAULT_PLAYER_SYMBOL[1];
        this->emptySymbol = ' ';
    }

    // ADDITIONAL OVERLOADED CONSTRUCTORS. 
    // -----------------------------------

    PlayerSymbol(char playerOne, char playerTwo, char emptySymbol = ' ') {
        this->playerOne = playerOne;
        this->playerTwo = playerTwo;
        this->emptySymbol = emptySymbol;
    }

    PlayerSymbol(char playerSymbol[2], char emptySymbol = ' ') {
        this->playerOne = playerSymbol[0];
        this->playerTwo = playerSymbol[1];
        this->emptySymbol = emptySymbol;
    }
};

#endif
