#include "logic/bot.hpp"
#include "logic/shooter.hpp"

Bot::Bot(Board* playerBoard)
{
    srand(time(NULL));
    botState = RandomShoot;
    this->playerBoard = playerBoard;
}

void Bot::randomShoot()
{
    bool canShoot;
    do
    {
        currentCursorPosition = Position(rand() % BOARD_SIZE, rand() % BOARD_SIZE);
        canShoot = playerBoard->canShoot(currentCursorPosition);
    } while (canShoot == false);
    CellType shootInfo = shoot(currentCursorPosition, playerBoard);
    if (shootInfo == Missed)
        return;

    currentShip = playerBoard->getShip(currentCursorPosition);
    if (currentShip == nullptr)
        return;

    if (currentShip->isDestroyed)
        return;

    shipPosition = currentCursorPosition;
    botState = FindDirection;
    makeStep();
}

void Bot::findDirection()
{
    Position shootPosition = shipPosition + shootDirections[shootDirection % 4];
    while(shootPosition.y >= BOARD_SIZE || shootPosition.x >= BOARD_SIZE
        || shootPosition.y < 0 || shootPosition.x < 0)
    {
        shootDirection++;
        shootPosition = shipPosition + shootDirections[shootDirection % 4];
    }

    CellType shootInfo = shoot(shootPosition, playerBoard);
    if (shootInfo == Missed)
    {
        shootDirection++;
        return;
    }
    
    if (currentShip == nullptr)
    {
        botState = RandomShoot;
        return;
    }

    if (currentShip->isDestroyed)
    {
        currentShip = nullptr;
        botState = RandomShoot;
    }
    else
    {
        currentCursorPosition = shootPosition;
        botState = FishiningOff;
    }
    makeStep();
}

void Bot::fishiningOff()
{   
    Position shootPosition = currentCursorPosition + shootDirections[shootDirection % 4];
    CellType shootInfo = shoot(shootPosition, playerBoard);
    if (currentShip == nullptr)
    {
        botState = RandomShoot;
        currentCursorPosition = shootPosition;
        return;
    }

    if (currentShip->isDestroyed)
    {
        currentShip = nullptr;
        botState = RandomShoot;
        currentCursorPosition = shootPosition;
        makeStep();
        return;
    }
    else
    {
        if (shootInfo == Missed)
        {
            shootDirection = (shootDirection + 2) % 4;
            currentCursorPosition = shipPosition;
        }
        else
        {
            currentCursorPosition = shootPosition;
            makeStep();
        }
    }
}

void Bot::makeStep()
{
    switch (botState)
    {
    case RandomShoot:
        randomShoot();
        break;
    case FindDirection:
        findDirection();
        break;
    case FishiningOff:
        fishiningOff();
        break;
    default:
        break;
    }
}