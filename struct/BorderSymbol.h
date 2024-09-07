#ifndef BORDERSYMBOL_H
#define BORDERSYMBOL_H

#include "../helpers/Tools.h"

const char DEFAULT_SYMBOL[2] = {'-', '|'};
const char SELECTED_SYMBOL[2] = {'*', '*'};

/**
 * @brief A simple struct to store the coordinates of the nineboard grid.
 */
struct BorderSymbol
{
    char defaultSymbol[2];
    char selectedSymbol[2];

    // Default constructor
    BorderSymbol()
        : defaultSymbol{DEFAULT_SYMBOL[0], DEFAULT_SYMBOL[1]},
          selectedSymbol{SELECTED_SYMBOL[0], SELECTED_SYMBOL[1]}
    {
    }
    // ADDITIONAL OVERLOADED CONSTRUCTORS.
    // -----------------------------------

    BorderSymbol(const char defaultSymbol[2], const char selectedSymbol[2])
        : defaultSymbol{defaultSymbol[0], defaultSymbol[1]},
          selectedSymbol{selectedSymbol[0], selectedSymbol[1]}
    {
    }
};

#endif
