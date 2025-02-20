#pragma once
#include "logic/board.hpp"

enum BotState
{
    RandomShoot,
    FindDirection,
    FishiningOff
};

class Bot
{
private:
    Board* playerBoard;
    BotState botState;
    unsigned short shootDirection = 0;
    std::vector<Position> shootDirections = 
    {
        Position(0, 1),
        Position(1, 0),
        Position(0, -1),
        Position(-1, 0)
    };
    Position currentCursorPosition;
    Position shipPosition;
    Ship* currentShip = nullptr;
    void randomShoot();
    void findDirection();
    void fishiningOff();
public:
    Bot(Board* playerBoard);
    void makeStep();
};