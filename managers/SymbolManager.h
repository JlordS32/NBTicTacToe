#ifndef SYMBOLMANAGER_H_
#define SYMBOLMANAGER_H_

#include "../struct/BorderSymbol.h"
#include "../struct/PlayerSymbol.h"

class SymbolManager
{
private:
    BorderSymbol borderSymbol;
    PlayerSymbol playerSymbol;

public:
    // Constructor
    SymbolManager() : borderSymbol(), playerSymbol() {}

    // Overloaded constructor for custom symbols
    SymbolManager(BorderSymbol borderSymbol, PlayerSymbol playerSymbol)
    {
        this->borderSymbol = borderSymbol;
        this->playerSymbol = playerSymbol;
    }

    PlayerSymbol* getPlayerSymbol()
    {
        return &this->playerSymbol;
    }
    void setPlayerSymbol(PlayerSymbol playerSymbol)
    {
        this->playerSymbol = playerSymbol;
    }

    BorderSymbol* getBorderSymbol()
    {
        return &this->borderSymbol;
    }
    void setBorderSymbol(BorderSymbol borderSymbol)
    {
        this->borderSymbol = borderSymbol;
    }
};

#endif
