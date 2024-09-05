#ifndef BOARDMANAGER_H_
#define BOARDMANAGER_H_

#include "../struct/Coordinate.h"
#include "./SymbolManager.h"
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
    BoardManager(TicTacToe (*grid)[3][3], Coordinate *currentBoard, SymbolManager *symbolManager) : nbTicTacToe(symbolManager->getPlayerSymbol(), symbolManager->getBorderSymbol())
    {
        this->grid = grid;
        this->currentBoard = currentBoard;
    }

    // PUBLIC METHODS
    void switchBoard(const Move currentPlayer);
    void displayBoard();
    void displayCurrentBoardPos();
    void displayLastBoardPos();
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

    // Check if the next board to be switched is full
    TicTacToe *board = &(*grid)[boardX][boardY];
    bool isBoardFull = Tools::isBoardFull(board);

    while (isBoardFull)
    {
        // Generate random coordinates
        Tools::generateRandomMove(&boardX, &boardY);

        // Update current board
        board = &(*grid)[boardX][boardY];

        // Check if the next board to be switched is full
        isBoardFull = Tools::isBoardFull(board);
    }

    // Assign new board coordinates if valid.
    this->currentBoard->x = boardX;
    this->currentBoard->y = boardY;
}

#endif