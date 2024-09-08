/*
 * TicTacToe.h
 *
 *  Created on: 5 Aug 2023
 *      Author: 2002345
 */

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include "./struct/Move.h"

const int SIZE = 3;

class TicTacToe
{
private:
	int board[SIZE][SIZE];

public:
	/**
	 * @brief Constructor
	 *
	 * This function is called when the object is created. This function is a constructor, since this function does not have any paremeters, it'll be automatically loaded without any parameters.
	 */
	TicTacToe();

	// PUBLIC METHODS
	int noOfMoves;
	bool isValidMove(const int x, const int y);
	int gameStatus();

	// Move setter
	// +1 overload
	void addMove(const int x, const int y, const int player);
	void addMove(const Move *player);

	// Getter for the board
	int getCell(const int x, const int y);

	// Getter for the number of moves
	int getNoOfMoves();
};

TicTacToe::TicTacToe()
{
	// Dynamically allocate all values in the board 0. 0 = empty
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			this->board[row][col] = 0;

	// Set the number of moves
	this->noOfMoves = 0;

	// // Uncomment to test draw states and comment the above code.
	// board[0][0] = 0;
	// board[0][1] = 1;
	// board[0][2] = -1;
	// board[1][0] = 0;
	// board[1][1] = 0;
	// board[1][2] = 0;
	// board[2][0] = 0;
	// board[2][1] = -1;
	// board[2][2] = 1;

	// this->noOfMoves = 4;
}

/**
 * @brief Checks value of the board given the parameters
 *
 * @param x The x value
 * @param y The y value
 *
 * @return The value of the board
 */
int TicTacToe::getCell(int x, int y)
{
	return this->board[x][y];
}

/**
 * @brief Checks if a move is valid
 *
 * Condition: x and y is between 0 and 2 (inclusive) and the position according
 * to board is actually empty (0).
 *
 * @param x The x value corresponding to the board.
 * @param y The y value corresponding to the board.
 *
 * @return `true` if the move is valid, `false` if the move is invalid.
 */
bool TicTacToe::isValidMove(int x, int y)
{
	return (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == 0);
}

/**
 * @brief Adds a move to the board
 *
 * Think of this function as an updater. This simply just updates the current value of our private variable 'board'. This function is responsible as to why we're able to pass O and X into the board.
 */
void TicTacToe::addMove(int x, int y, int player)
{
	// We reduce the number of moves if the move is gonna be undone.
	// This is purpose made for the algorithms.
	if (player == 0)
	{
		this->noOfMoves--;
	}
	else
	{
		this->noOfMoves++;
	}

	// Add move
	this->board[x][y] = player;
}

/**
 * @brief Adds a move to the board
 *
 * Overlodded version. Takes a Move struct instead.
 *
 */
void TicTacToe::addMove(const Move *player)
{
	this->noOfMoves++;

	// Add move
	this->board[player->x][player->y] = player->currentPlayer;
}

/**
 * @brief Checks the status of the game
 *
 * @return `0` if the game is still in progress, `1` if the game is a draw, `2` if the game is won.
 */
int TicTacToe::gameStatus()
{
	// Check rows for a win
	for (int i = 0; i < 3; i++)
	{
		if (this->board[i][0] != 0 && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2])
			return this->board[i][0];
	}

	// Check columns for a win
	for (int i = 0; i < 3; i++)
	{
		if (this->board[0][i] != 0 && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i])
			return this->board[0][i];
	}

	// Check diagonals for a win
	if (this->board[0][0] != 0 && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2])
		return this->board[0][0];

	if (this->board[0][2] != 0 && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0])
		return this->board[0][2];

	// Check for draws
	if (this->noOfMoves >= 9)
	{
		return 2; // Signal it's a draw.
	}

	return 0; // The game is still ongoing.
}

int TicTacToe::getNoOfMoves() {
	return this->noOfMoves;
}

#endif
