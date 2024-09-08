#ifndef BOARDMANAGER_H_
#define BOARDMANAGER_H_

#include "./SymbolManager.h"
#include "../NBTicTacToe.h"
#include "../TicTacToe.h"
#include "../struct/Coordinate.h"
#include "../struct/Move.h"
#include "../helpers/Tools.h"

class BoardManager
{
private:
    NBTicTacToe nbTicTacToe;
    Coordinate *currentBoard;
    TicTacToe (*grid)[3][3];

public:
    /**
     * @brief Contructor
     *
     * Takes a pointer to the coordinate of the current board.
     */
    BoardManager(TicTacToe (*grid)[3][3], Coordinate *currentBoard, SymbolManager *symbolManager)
        : nbTicTacToe(symbolManager->getPlayerSymbol(), symbolManager->getBorderSymbol()),
          currentBoard(currentBoard),
          grid(grid) {}

    // PUBLIC METHODS
    void switchBoard(const Move currentPlayer);
    void displayBoard();
    void displayCurrentBoardPos();
    void displayLastBoardPos();
    void setRandomBoard();
};

/**
 * @brief Displays the board
 */
void BoardManager::displayBoard()
{
    nbTicTacToe.displayBoards(this->grid, *this->currentBoard);
}

/**
 * @brief Displays current the board
 */
void BoardManager::displayCurrentBoardPos()
{
    // This section is just a divider between the player's turn.
    cout << "---------------------------------------------------------------" << endl;
    cout << "CURRENT BOARD: " << this->currentBoard->x + 1 << ", " << this->currentBoard->y + 1 << endl;
    cout << "---------------------------------------------------------------" << endl
         << endl;
}

/**
 * @brief Displays the last the board
 */
void BoardManager::displayLastBoardPos()
{
    // This section is just a divider between the player's turn.
    cout << "---------------------------------------------------------------" << endl;
    cout << "LAST BOARD: " << this->currentBoard->x + 1 << ", " << this->currentBoard->y + 1 << endl;
}

/**
 * @brief Switches the board
 *
 * The board switching logic is random at the start. Board switches depending on the position of the player, if the next player is forced to go to full board. Randomly switch to a different board.
 *
 * @param x X coordinate
 * @param y Y coordinate
 */
void BoardManager::switchBoard(const Move currentPlayer)
{
    int boardX = currentPlayer.x;
    int boardY = currentPlayer.y;

    // Check if the board is full
    TicTacToe *board = &(*this->grid)[this->currentBoard->x][this->currentBoard->y];
    if (Tools::isBoardFull(board))
    {
        this->setRandomBoard();
    }
    // Otherwise the next board will based on the player move.
    else
    {
        this->currentBoard->x = boardX;
        this->currentBoard->y = boardY;
    }
}

void BoardManager::setRandomBoard()
{
    int boardX, boardY;
    bool isBoardFull = true;

    while (isBoardFull)
    {
        // Generate random move
        Tools::generateRandomMove(&boardX, &boardY);

        // Get board and evaluate if the board is full.
        TicTacToe *board = &(*this->grid)[boardX][boardY];
        isBoardFull = Tools::isBoardFull(board);

        // If the board is not full, assign the coords.
        // This loop should then terminate.
        if (!isBoardFull)
        {
            this->currentBoard->x = boardX;
            this->currentBoard->y = boardY;
        }
    }
}

#endif
