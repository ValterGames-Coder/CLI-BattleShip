#include "logic/bot.hpp"
#include "logic/shooter.hpp"

Bot::Bot(Difficulty difficulty, Board* playerBoard)
{
    srand(time(NULL));
    missedSteps = (unsigned short)difficulty;
    if (missedSteps == 0)
        botState = RandomShoot;
    else
        botState = MissedShoot;
    this->playerBoard = playerBoard;
}

void Bot::missedShoot()
{
    std::vector<Position> emptyPositions = playerBoard->getCells(Empty);
    shoot(emptyPositions[rand() % emptyPositions.size()], playerBoard);
    missedSteps--;
    if (missedSteps == 0)
        botState = RandomShoot;
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
    //CellType shootInfo = botShoot(currentCursorPosition);
    if (shootInfo == Missed)
        return;

    currentShip = playerBoard->getShip(currentCursorPosition);
    if (currentShip == nullptr || currentShip->isDestroyed)
        return;

    shipPosition = currentCursorPosition;
    botState = FindDirection;
    //makeStep();
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
    //makeStep();
}

void Bot::fishiningOff()
{
    Position shootPosition = currentCursorPosition + shootDirections[shootDirection % 4];
    CellType shootInfo = shoot(shootPosition, playerBoard);
    if (currentShip->isDestroyed)
    {
        currentShip = nullptr;
        botState = RandomShoot;
        currentCursorPosition = shootPosition;
        return;
    }
    else
    {
        if (shootInfo == Missed)
        {
            shootDirection = (shootDirection + 2) % 4;
            currentCursorPosition = shipPosition;
            //bot_state = FindDirection;
            //shootDirection++;
            //botState = FindDirection;
        }
        else
            currentCursorPosition = shootPosition;
    }
}

void Bot::makeStep()
{
    switch (botState)
    {
    case MissedShoot:
        missedShoot();
        break;
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