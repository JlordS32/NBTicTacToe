#ifndef move
#define move

/**
 * @brief Struct to manage player movements.
 * 
 * 1 = PLAYER O
 * -1 = PLAYER X
 */
struct Move
{
    int x;
    int y;
    int currentPlayer;

    Move(int x, int y, int player) {
        this->x = x;
        this->y = y;
        this->currentPlayer = player;
    }
};

#endif
