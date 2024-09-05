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

    BorderSymbol() {
        this->defaultSymbol[0] = DEFAULT_SYMBOL[0];
        this->defaultSymbol[1] = DEFAULT_SYMBOL[1];
        this->selectedSymbol[0] = SELECTED_SYMBOL[0];
        this->selectedSymbol[1] = SELECTED_SYMBOL[1];
    }

    // ADDITIONAL OVERLOADED CONSTRUCTORS. 
    // -----------------------------------

    BorderSymbol(char defaultSymbol[2], char selectedSymbol[2]) {
        this->defaultSymbol[0] = defaultSymbol[0];
        this->defaultSymbol[1] = defaultSymbol[1];
        this->selectedSymbol[0] = selectedSymbol[0];
        this->selectedSymbol[1] = selectedSymbol[1];
    }
};

#endif
