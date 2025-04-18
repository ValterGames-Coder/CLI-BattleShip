#include "logic/bot.hpp"
#include "logic/shooter.hpp"

Bot::Bot(Board* playerBoard)
{
    srand(time(NULL));
    m_botState = RandomShoot;
    m_playerBoard = playerBoard;
}

void Bot::randomShoot()
{
    bool canShoot;
    do
    {
        m_currentCursorPosition = Position(rand() % BOARD_SIZE, rand() % BOARD_SIZE);
        canShoot = m_playerBoard->canShoot(m_currentCursorPosition);
    } while (canShoot == false);
    CellType shootInfo = shoot(m_currentCursorPosition, m_playerBoard);
    if (shootInfo == Missed)
        return;

    m_currentShip = m_playerBoard->getShip(m_currentCursorPosition);
    if (m_currentShip == nullptr)
        return;

    if (m_currentShip->isDestroyed)
        return;

    m_shipPosition = m_currentCursorPosition;
    m_botState = FindDirection;
    makeStep();
}

void Bot::findDirection()
{
    Position shootPosition = m_shipPosition + m_shootDirections[m_shootDirection % 4];
    while(shootPosition.y >= BOARD_SIZE || shootPosition.x >= BOARD_SIZE
        || shootPosition.y < 0 || shootPosition.x < 0)
    {
        m_shootDirection++;
        shootPosition = m_shipPosition + m_shootDirections[m_shootDirection % 4];
    }

    CellType shootInfo = shoot(shootPosition, m_playerBoard);
    if (shootInfo == Missed)
    {
        m_shootDirection++;
        return;
    }
    
    if (m_currentShip == nullptr)
    {
        m_botState = RandomShoot;
        return;
    }

    if (m_currentShip->isDestroyed)
    {
        m_currentShip = nullptr;
        m_botState = RandomShoot;
    }
    else
    {
        m_currentCursorPosition = shootPosition;
        m_botState = FishiningOff;
    }
    makeStep();
}

void Bot::fishiningOff()
{   
    Position shootPosition = m_currentCursorPosition + m_shootDirections[m_shootDirection % 4];
    CellType shootInfo = shoot(shootPosition, m_playerBoard);
    if (m_currentShip == nullptr)
    {
        m_botState = RandomShoot;
        m_currentCursorPosition = shootPosition;
        return;
    }

    if (m_currentShip->isDestroyed)
    {
        m_currentShip = nullptr;
        m_botState = RandomShoot;
        m_currentCursorPosition = shootPosition;
        makeStep();
        return;
    }
    else
    {
        if (shootInfo == Missed)
        {
            m_shootDirection = (m_shootDirection + 2) % 4;
            m_currentCursorPosition = m_shipPosition;
        }
        else
        {
            m_currentCursorPosition = shootPosition;
            makeStep();
        }
    }
}

void Bot::makeStep()
{
    switch (m_botState)
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