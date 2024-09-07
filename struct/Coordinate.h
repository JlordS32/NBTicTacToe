#ifndef COORDINATE_H
#define COORDINATE_H

#include "../helpers/Tools.h"
#include <cstdlib>
#include <ctime>

/**
 * @brief A simple struct to store the coordinates of the nineboard grid.
 */
struct Coordinate
{
    int x;
    int y;

    Coordinate()
    {
        srand(time(0));
        Tools::generateRandomMove(&this->x, &this->y);
    }

    Coordinate(int x, int y)
        : x(x),
          y(y)
    {
    }
};

#endif
