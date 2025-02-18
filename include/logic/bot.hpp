#pragma once
#include "logic/board.hpp"

enum Difficulty
{
    Easy = 10,
    Normal = 5,
    Hard = 0
};

enum BotState
{
    MissedShoot,
    RandomShoot,
    FindDirection,
    FishiningOff
};

class Bot
{
private:
    Board* playerBoard;
    BotState botState;
    unsigned short missedSteps = 10;
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
    void missedShoot();
    void randomShoot();
    void findDirection();
    void fishiningOff();
public:
    Bot(Difficulty difficulty, Board* playerBoard);
    void makeStep();
};