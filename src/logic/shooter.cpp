#include "logic/shooter.hpp"

CellType shoot(Position position, Board* board)
{
    if (board->getLayer(Ships).count(position))
    {
        Ship* ship = board->getShip(position);
        ship->takeDamage(position);
        return Hit;
    }
    else
    {
        wprintw(stdscr, "%li", board->getLayer(Water).count(position));
        board->getLayer(Water)[position].updateType(Missed);
        return Missed;
    }
}