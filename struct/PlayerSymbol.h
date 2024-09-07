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

    PlayerSymbol()
        : playerOne(DEFAULT_PLAYER_SYMBOL[0]),
          playerTwo(DEFAULT_PLAYER_SYMBOL[1]),
          emptySymbol(' ')
    {
    }

    // ADDITIONAL OVERLOADED CONSTRUCTORS.
    // -----------------------------------

    PlayerSymbol(char playerOne, char playerTwo, char emptySymbol = ' ')
        : playerOne(playerOne),
          playerTwo(playerTwo),
          emptySymbol(emptySymbol)
    {
    }
    PlayerSymbol(char playerSymbol[2], char emptySymbol = ' ') :
        playerOne(playerSymbol[0]),
        playerTwo(playerSymbol[1]),
        emptySymbol(emptySymbol)
    {
    }
};

#endif
