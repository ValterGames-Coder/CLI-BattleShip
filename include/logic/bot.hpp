#pragma once
#include "logic/board.hpp"
#include <cstdlib>
#include <ctime>

enum BotState
{
    RandomShoot,
    FindDirection,
    FishiningOff
};

class Bot
{
private:
    Board* m_playerBoard;
    BotState m_botState;
    unsigned m_shootDirection = 0;
    std::vector<Position> m_shootDirections = 
    {
        Position(0, 1),
        Position(1, 0),
        Position(0, -1),
        Position(-1, 0)
    };
    Position m_currentCursorPosition;
    Position m_shipPosition;
    Ship* m_currentShip = nullptr;
    void randomShoot();
    void findDirection();
    void fishiningOff();
public:
    Bot(Board* playerBoard);
    void makeStep();
};