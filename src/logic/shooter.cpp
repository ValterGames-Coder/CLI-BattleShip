#include "logic/shooter.hpp"

CellType shoot(Position position, Board* board)
{
    if (board->getLayer(Ships).count(position))
    {
        Ship* ship = board->getShip(position);
        ship->takeDamage(position);
        board->update();
        return Hit;
    }
    else
    {
        board->getLayer(Water)[position].updateType(Missed);
        board->update();
        return Missed;
    }
}