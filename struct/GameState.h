#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
 * @brief Struct to manage the state of the game.
 * 
 * GAME STATES = 
 * 0 = IN PROGRESS,
 * 1 = PLAYER WON,
 * -1 = COMPUTER WON,
 * 2 = DRAW
 * 
 * @param status = GAME STATES
 * @param currentPlayer = 1 OR -1
 */
struct GameState {
    int status; 
    Move currentPlayer;

	// Initialise game status and currentPlayer.
	GameState(int running, int player) : currentPlayer(-1, -1, player) {
		this->status = running;
	}
};

#endif