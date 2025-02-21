#include "logic/shooter.hpp"
#include "animation/animator.hpp"

CellType shoot(Position position, Board* board)
{
    // unsigned short xMax, yMax;
    // getmaxyx(stdscr, yMax, xMax);
    if (board->getLayer(Ships).count(position))
    {
        Ship* ship = board->getShip(position);
        // Position rocketSize = getSize("./img/rocket.txt");
        // Position startRocketPosition {(short)(yMax - rocketSize.y), position.x};
        // Position endRocketPosition = position;
        // Animation::move(stdscr, startRocketPosition, endRocketPosition, "./img/rocket.txt", 2, COLOR_RED & COLOR_YELLOW);
        // wclear(stdscr);
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