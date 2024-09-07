#ifndef NBGAME_H_
#define NBGAME_H_

#include "./TicTacToe.h"
#include "./NBTicTacToe.h"
#include "./managers/BoardManager.h"
#include "./managers/PlayerManager.h"
#include "./managers/SymbolManager.h"
#include "./helpers/Menu.h"
#include "./helpers/Tools.h"
#include "./struct/Move.h"
#include "./struct/Coordinate.h"
#include "./struct/GameState.h"

const int RUNNING = 0;
const int PLAYER_X = 1;
const int PLAYER_O = -1;

class NBGame
{
private:
	// CLASS INSTANCES
	TicTacToe grid[3][3];
	Coordinate currentBoard;
	BoardManager boardManager;
	PlayerManager playerManager;
	SymbolManager symbolManager;
	Menu menu;

	// GAME STATE
	GameState gameState;
	int turnCounter;

	// GAME FUNCTIONS
	void start();
	void gameLoop();
	void displayBoard();
	void handleMove();
	void switchBoard();
	void displayNumberOfTurns();

public:
	/**
	 * @brief Construct a new NBGame object
	 *
	 * When the object is created. Randomly select a random location on the 3 x 3
	 * board as the initial starting point of the game.
	 *
	 * Going forward, the board position will be determined based on the player's turn.
	 */
	NBGame()
		: grid(),
		  currentBoard(),
		  symbolManager(),
		  playerManager(&grid, &currentBoard, &symbolManager),
		  boardManager(&grid, &currentBoard, &symbolManager),
		  menu(&symbolManager),
		  gameState(RUNNING, PLAYER_X),
		  turnCounter(0)
	{
	}

	void play();
};

/**
 * @brief Plays the game
 *
 * This is the central point of the whole game. Everything is being ran here.
 */
void NBGame::play()
{
	start();
	gameLoop();
}

void NBGame::start()
{
	// Start the game with a menu screen.
	menu.welcomeScreen();

	// Select player one and player two. O and X respectively.
	int playerOneSelection = menu.displayPlayerSelection(PLAYER_X);
	int playerTwoSelection = menu.displayPlayerSelection(PLAYER_O);

	// Set the selected player by initialising from the player manager class.
	playerManager.initializePlayers(playerOneSelection, playerTwoSelection);

	// Display starting board.
	displayBoard();
}

void NBGame::gameLoop()
{
	while (this->gameState.status == RUNNING)
	{
		handleMove();
		this->turnCounter++;
		displayBoard();
		switchBoard();

		// CHECK GAME STATUS
		playerManager.checkGameStatus(this->gameState.status);

		// SWITCH PLAYER
		playerManager.switchPlayer(&this->gameState.currentPlayer);
	}
}

void NBGame::handleMove()
{
	// Display current player
	playerManager.displayCurrentPlayer(this->gameState.currentPlayer);

	displayNumberOfTurns();

	// Get input from player.
	playerManager.handleMove(&this->gameState.currentPlayer, &this->gameState.status);
}

void NBGame::switchBoard()
{
	// Hard coded statement
	// Once the game is over there's no need To switch board or display board.
	if (this->gameState.status == RUNNING)
	{
		boardManager.displayLastBoardPos();
		boardManager.switchBoard(this->gameState.currentPlayer);

		boardManager.displayCurrentBoardPos();

		displayBoard();
	}
}

void NBGame::displayBoard()
{
	boardManager.displayBoard();
}

void NBGame::displayNumberOfTurns()
{
	// Display the number of turns and the last move after the first move.
	if (this->gameState.currentPlayer.x != -1 && this->gameState.currentPlayer.y != -1)
	{
		cout << "Number of turns: " << this->turnCounter << endl;
		cout << "Last move: " << this->gameState.currentPlayer.x + 1 << ", " << this->gameState.currentPlayer.y + 1 << endl
			 << endl;
	}
}

#endif