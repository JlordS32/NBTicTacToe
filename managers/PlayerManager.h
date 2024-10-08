#ifndef PLAYERMANAGER_H_
#define PLAYERMANAGER_H_

#include "./SymbolManager.h"
#include "../TicTacToe.h"
#include "../players/base/Player.h"
#include "../players/HumanPlayer.h"
#include "../players/AdvancedMinimaxPlayer.h"
#include "../players/MonteCarloPlayer.h"
#include "../players/MinimaxPlayer.h"
#include "../players/RandomPlayer.h"
#include "../players/SmartPlayer.h"
#include "../players/MindfulPlayer.h"
#include "../struct/Coordinate.h"
#include "../struct/Move.h"
#include "../struct/PlayerSymbol.h"

const int PM_BOARD_FULL = 9 * 9;
const int MANAGER_PLAYER_O = 1;
const int MANAGER_PLAYER_X = -1;
const int DRAW = 2;
const int MAX_NUM_SIMULATIONS = 10000;
const int MAX_DEPTH_LIMIT = 10;

class PlayerManager
{
private:
    // An array of pointers that can hold 2 Player objects (including derived classes).
    Player *players[2];
    TicTacToe (*grid)[3][3];
    Coordinate *currentBoard;
    PlayerSymbol *playerSymbol;

    // PRIVATE METHODS
    void checkDraw(int *gameStatus);
    int getNumSimulations(int player);
    int getDepthLimit(int player);

public:
    PlayerManager(TicTacToe (*grid)[3][3], Coordinate *currentBoard, SymbolManager *symbolManager)
        : grid(grid),
          currentBoard(currentBoard),
          playerSymbol(symbolManager->getPlayerSymbol())
    {
    }

    void handleMove(Move *currentPlayer, int *gameStatus);
    void switchPlayer(Move *player);
    void initializePlayers(const int playerOne, const int playerTwo);
    void displayCurrentPlayer(Move player) const;
    void checkGameStatus(const int gameStatus) const;

    // Destructor
    ~PlayerManager()
    {
        delete players[0];
        delete players[1];
    }
};

/**
 * @brief Handles the player's move
 *
 * @param currentPlayer 1 or -1
 * @param currentBoardStatus Take a reference of a variable to update the game status of the selected board.
 */
void PlayerManager::handleMove(Move *currentPlayer, int *gameStatus)
{
    // Get the current board
    TicTacToe *currentSubBoard = &(*this->grid)[this->currentBoard->x][this->currentBoard->y];

    // Delegate move to the correct player
    int player = currentPlayer->currentPlayer == 1 ? 0 : 1;
    players[player]->getMove(currentPlayer, this->currentBoard);

    // Update the board object
    currentSubBoard->addMove(currentPlayer);

    // Update the game status
    *gameStatus = currentSubBoard->gameStatus();

    // If the board is draw. Check the rest of the boards for draw.
    if (*gameStatus == 2)
    {
        checkDraw(gameStatus);
    }
}

void PlayerManager::checkDraw(int *gameStatus)
{
    int totalMoves = Tools::getTotalMoves(this->grid);

    if (totalMoves == PM_BOARD_FULL)
    {
        *gameStatus = 2;
    }
    else
    {
        *gameStatus = 0;
    }
}

/**
 * @brief Initializes the players
 *
 * Initialises player based on playerSelection. 1 = Human vs. Human, 2 = Human vs. Smart, 3 = Human vs. Random, 4 = Smart vs. Random, 5 = Smart vs. Smart.
 *
 * @param playerSelection 1, 2, 3, 4 or 5
 *
 */
void PlayerManager::initializePlayers(const int playerOne, const int playerTwo)
{
    const int selectedPlayers[2] = {playerOne, playerTwo};

    // Based on the playerSelection input, this function dynamically allocates and assigns derived class objects (Human, Computer, or RandomPlayer) to the players pointer array.
    // Each case corresponds to a specific player combination (e.g., Human vs. Human).
    // The dynamically allocated objects allow polymorphic behavior during gameplay.
    for (int i = 0; i < 2; i++)
    {
        // Get the player based on the current index.
        // 0 = 1
        // 1 = -1
        int player = (i == 0) ? 1 : -1;

        switch (selectedPlayers[i])
        {
        case 1: // Human Player
            players[i] = new HumanPlayer(this->grid);
            break;
        case 2: // Random Player
            players[i] = new RandomPlayer(this->grid);
            break;
        case 3: // Minimax Player
            players[i] = new MinimaxPlayer(this->grid, player);
            break;
        case 4: // Mindful Player
            players[i] = new MindfulPlayer(this->grid, player);
            break;
        case 5: // Smart Player
            players[i] = new SmartPlayer(this->grid, player);
            break;
        case 6: // Monte Carlo Player
            players[i] = new MonteCarloPlayer(this->grid, player, getNumSimulations(player));
            break;
        case 7: // Advanced Minimax Player
            players[i] = new AdvancedMinimaxPlayer(this->grid, player, getDepthLimit(player));
            break;
        default:
            break;
        }
    }
}

/**
 * @brief Gets the number of simulations
 *
 * A simply function that queries user for the number of simulations required for the Monte Claro Player.
 *
 * @return int
 */
int PlayerManager::getNumSimulations(int player)
{
    char symbol = player == 1 ? this->playerSymbol->playerOne : this->playerSymbol->playerTwo;
    int numSimulations;

    cout << "--------------------------------" << endl;
    cout << "MONTE CARLO PLAYER: " << symbol << endl;
    cout << "--------------------------------" << endl;

    // Get number of simulations
    cout << "Enter number of simulations (1-" << MAX_NUM_SIMULATIONS << "): ";
    while (!(cin >> numSimulations) || numSimulations < 1 || numSimulations > MAX_NUM_SIMULATIONS)
    {
        cout << "Invalid input. Please enter a number between 1 and " << MAX_NUM_SIMULATIONS << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    return numSimulations;
}

/**
 * @brief Gets the depth limit
 *
 * A simply function that queries user for depth search limit for the Advanced Minimax Player.
 *
 * @return int
 */
int PlayerManager::getDepthLimit(int player)
{
    char symbol = player == 1 ? this->playerSymbol->playerOne : this->playerSymbol->playerTwo;
    int depth;

    cout << "--------------------------------" << endl;
    cout << "ADVANCED MINIMAX PLAYER: " << symbol << endl;
    cout << "--------------------------------" << endl;

    // Get depth limit
    cout << "Enter depth limit (1-" << MAX_DEPTH_LIMIT << "): ";
    while (!(cin >> depth) || depth < 1 || depth > MAX_DEPTH_LIMIT)
    {
        cout << "Invalid input. Please enter a number between 1 and " << MAX_DEPTH_LIMIT << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << endl;

    return depth;
}

/**
 * @brief Switches the player
 *
 * @param currentPlayer
 */
void PlayerManager::switchPlayer(Move *player)
{
    player->currentPlayer = (player->currentPlayer == 1) ? -1 : 1;
}

/**
 * @brief Displays a header of the current player
 *
 * @param player The player symbol
 */
void PlayerManager::displayCurrentPlayer(Move player) const
{
    char symbol = player.currentPlayer == 1 ? this->playerSymbol->playerOne : this->playerSymbol->playerTwo;
    int currPlayer = player.currentPlayer == 1 ? 0 : 1;

    cout << "----------------------------------------------------------------" << endl;
    cout << "PLAYER "
         << symbol
         << " TURN: "
         << players[currPlayer]->getName()
         << " " << "Player " << currPlayer + 1
         << endl;
    cout << "----------------------------------------------------------------"
         << endl
         << endl;
}

/**
 * @brief Checks the game status
 *
 * Simply prints the result of the game.
 *
 * @param gameStatus
 */
void PlayerManager::checkGameStatus(int gameStatus) const
{
    char symbol = gameStatus == 1 ? this->playerSymbol->playerOne : this->playerSymbol->playerTwo;
    int currPlayer = gameStatus == 1 ? 0 : 1;

    // PRINT DRAW STATE
    if (gameStatus == DRAW)
    {
        cout << "-----------------------------------------------------------------" << endl
             << "\t\t\t    Draw! " << endl
             << "-----------------------------------------------------------------" << endl
             << endl;
    }

    // PRINT WIN STATE
    else if (gameStatus == MANAGER_PLAYER_O || gameStatus == MANAGER_PLAYER_X)
    {
        cout << "-----------------------------------------------------------------" << endl
             << "Player "
             << symbol
             << ": " << players[currPlayer]->getName() << " Player " << currPlayer + 1
             << " wins! "
             << endl
             << "-----------------------------------------------------------------" << endl
             << endl;
    }
}

#endif
