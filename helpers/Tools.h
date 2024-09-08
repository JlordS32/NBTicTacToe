#ifndef TOOLS_H
#define TOOLS_H

#include "../TicTacToe.h"
#include <cstdlib>

const int TOOLS_BOARD_SIZE = 3;

class Tools
{
public:
    static bool isBoardEmpty(TicTacToe *board);
    static bool isBoardFull(TicTacToe *board);
    static int checkValues(TicTacToe *board, int valueToCheck);
    static void generateRandomMove(int *x, int *y);
    static char getBorderSymbol(bool condition, char defaultChar, char selectedChar);
    static int getTotalMoves(TicTacToe (*grid)[TOOLS_BOARD_SIZE][TOOLS_BOARD_SIZE]);
};

/**
 * @brief Checks if the board is empty
 *
 * @param board Takes a pointer to board
 * @return true if the board is empty
 * @return false if the board is not empty
 */
bool Tools::isBoardEmpty(TicTacToe *board)
{

    for (int i = 0; i < TOOLS_BOARD_SIZE; i++)
    {

        for (int j = 0; j < TOOLS_BOARD_SIZE; j++)
        {
            if (board->getCell(i, j) != 0)
            {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief Checks if the board is full
 *
 * @param board Takes a pointer to board
 * @return true if the board is full
 * @return false if the board is not full
 */
bool Tools::isBoardFull(TicTacToe *board)
{

    for (int i = 0; i < TOOLS_BOARD_SIZE; i++)
    {
        for (int j = 0; j < TOOLS_BOARD_SIZE; j++)
        {
            if (board->getCell(i, j) == 0)
            {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief Checks the number of occurences on the board.
 * 
 * @param board A pointer to board.
 * @param valueToCheck The specific value to check inside the board.
 * 
 * @return The number of occurences
 */
int Tools::checkValues(TicTacToe *board, int valueToCheck)
{

    int numberOfOccurences = 0;
    for (int i = 0; i < TOOLS_BOARD_SIZE; i++)
    {
        for (int j = 0; j < TOOLS_BOARD_SIZE; j++)
        {
            if (board->getCell(i, j) == valueToCheck)
            {
                numberOfOccurences++;
            }
        }
    }
    return numberOfOccurences;
}

/**
 * @brief Generates a random move
 *
 * IMPORTANT: Must implement the seed on the caller side.
 * 
 * @param x A pointer to x value.
 * @param y A pointer to y value.
 */
void Tools::generateRandomMove(int *x, int *y)
{
    // Randomly select for row
    *x = rand() % TOOLS_BOARD_SIZE;

    // Randomly select for col
    *y = rand() % TOOLS_BOARD_SIZE;
}

/**
 * @brief Gets a border symbol conditionally
 *
 * It's simply just a ternary operator that returns a char symbol that's been encapsulated into a function for reusability.
 *
 * @param condition A boolean expression
 * @param defaultChar The default character
 * @param selectedChar The selected character
 *
 * @return char The selected character
 */
char Tools::getBorderSymbol(bool condition, char defaultChar, char selectedChar)
{
    return condition ? selectedChar : defaultChar;
}

int Tools::getTotalMoves(TicTacToe (*grid)[TOOLS_BOARD_SIZE][TOOLS_BOARD_SIZE])
{
    int totalMoves = 0;

    // Loop through each individual boards in the grid.
    for (int i = 0; i < TOOLS_BOARD_SIZE; i++)
    {
        for (int j = 0; j < TOOLS_BOARD_SIZE; j++)
        {
            TicTacToe *board = &(*grid)[i][j];
            totalMoves += board->getNoOfMoves();
        }
    }

    return totalMoves;
}

#endif