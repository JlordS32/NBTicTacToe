#ifndef NBTicTacToe_H
#define NBTicTacToe_H

#include "TicTacToe.h"
#include "./struct/Coordinate.h"
#include "./struct/PlayerSymbol.h"
#include "./struct/BorderSymbol.h"
#include "./struct/Move.h"
#include "./helpers/Tools.h"

const int GRID_SIZE = 3;
const int LINE_WIDTH = 19;
const int THICKNESS = 2;

class NBTicTacToe
{
private:
    // PRIVATE METHODS
    void printHorizontalLine(const int &row, const Coordinate &currentBoard);
    void printInnerRow(TicTacToe *board, const int innerRow, const char borderSymbol);
    void printCell(TicTacToe *board, const int row);
    void printDividerLine(const int row, const Coordinate &currentBoard, const int innerRow);

    // CLASS ATTRIBUTES
    PlayerSymbol *playerSymbol;
    BorderSymbol *border;

public:
    // CONSTRUCTORS
    NBTicTacToe(PlayerSymbol *playerSymbol, BorderSymbol *border)
        : playerSymbol(playerSymbol),
          border(border)
    {
    }

    // PUBLIC METHODS
    void displayBoards(TicTacToe (*grid)[3][3], const Coordinate currentBoard);
};

/**
 * @brief Displays the 3x3 TicTacToe grid on the terminal
 *
 * This functions is the main function for printing the 3x3 TicTacToe grid.
 *
 * @param grid A point to the 3x3 TicTacToe grid
 * @param currentBoard The pointer to board coordinates.
 */
void NBTicTacToe::displayBoards(TicTacToe (*grid)[3][3], const Coordinate currentBoard)
{
    // First for loop: Row
    for (int row = 0; row < GRID_SIZE; row++)
    {
        // Print the horizontal line for the top bit of the each row.
        printHorizontalLine(row, currentBoard);

        // Second for loop: Inner row (the row inside Board x, y)
        for (int innerRow = 0; innerRow < GRID_SIZE; innerRow++)
        {
            char borderSymbol;

            // Third for loop: Setup for the column of the board.
            for (int col = 0; col < GRID_SIZE; col++)
            {
                // Conditionally get the borderSymbol.
                // If we're in the selected zone of x and y, we get * for the border symbol.
                bool condition = row == currentBoard.x && col == currentBoard.y;
                char borderSymbol = Tools::getBorderSymbol(condition, this->border->defaultSymbol[1], this->border->selectedSymbol[1]);

                // Get current board.
                TicTacToe *board = &(*grid)[row][col];

                // Print each cell in the inner row.
                printInnerRow(board, innerRow, borderSymbol);
            }

            cout << endl;

            printDividerLine(row, currentBoard, innerRow);

            // If we're in the middle row
            // we add an additional "|  |"
            if (innerRow == 0)
            {
                cout << endl;

                for (int i = 0; i < GRID_SIZE; i++)
                {
                    bool condition = row == currentBoard.x && i == currentBoard.y;
                    borderSymbol = Tools::getBorderSymbol(condition, this->border->defaultSymbol[1], this->border->selectedSymbol[1]);

                    cout << borderSymbol;
                    cout << "     |     |     ";
                    cout << borderSymbol;
                    cout << "   ";
                }
            }

            cout << endl;
        }

        // Print the horizontal line for the bottom bit of the each row.
        printHorizontalLine(row, currentBoard);

        cout << endl;
    }
}

/**
 * @brief Displays the horizontal line for the top and bottom of each 3x3 TicTacToe grid.
 *
 * All parameters are passed by reference.
 *
 * @param row The current row.
 * @param currentBoard The pointer to board coordinates.
 */
void NBTicTacToe::printHorizontalLine(const int &row, const Coordinate &currentBoard)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < LINE_WIDTH; j++)
        {
            if (j % THICKNESS == 0 && j != 0 && j != (LINE_WIDTH - 1))
            {
                bool condition = row == currentBoard.x && i == currentBoard.y;
                cout << Tools::getBorderSymbol(condition, this->border->defaultSymbol[0], this->border->selectedSymbol[0]);
            }
            else
                cout << " ";
        }
        cout << "   ";
    }

    cout << endl;
}

/**
 * @brief Prints the inner row of the 3x3 TicTacToe grid
 *
 * Uses printCell() to print the values in each cell.
 *
 * @param board The pointer to the 3x3 TicTacToe grid
 * @param innerRow The inner row
 * @param borderSymbol The border symbol
 */
void NBTicTacToe::printInnerRow(TicTacToe *board, const int innerRow, const char borderSymbol)
{
    // Left border
    cout << borderSymbol;

    // Print cell
    printCell(board, innerRow);

    // Right border
    cout << borderSymbol;

    // Space out
    cout << "   ";
}

/**
 * @brief Prints the inner row of the 3x3 TicTacToe grid
 *
 * @param grid The 3x3 TicTacToe grid
 * @param row The row
 * @param borderSymbol The default border symbol
 */
void NBTicTacToe::printCell(TicTacToe *board, const int row)
{
    // Printing the current row and passing the inner row.
    char symbol = ' ';

    // Render each value in the cell.
    for (int i = 0; i < 3; i++)
    {
        if (board->getCell(row, i) == 1)
            symbol = this->playerSymbol->playerOne;
        else if (board->getCell(row, i) == -1)
            symbol = this->playerSymbol->playerTwo;
        else
            symbol = this->playerSymbol->emptySymbol;

        cout << "  " << symbol << "  ";

        if (i != 2)
            cout << "|";
    }
}

/**
 * @brief Prints the divider line between rows of each board.
 */
void NBTicTacToe::printDividerLine(const int row, const Coordinate &currentBoard, const int innerRow)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        bool condition = row == currentBoard.x && i == currentBoard.y;
        char borderSymbol = Tools::getBorderSymbol(condition, this->border->defaultSymbol[1], this->border->selectedSymbol[1]);

        if (innerRow != 2)
            cout << borderSymbol << "_ _ _|_ _ _|_ _ _" << borderSymbol << "   ";
        else
            cout << borderSymbol << "     |     |     " << borderSymbol << "   ";
    }
}

#endif