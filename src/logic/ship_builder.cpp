#include "logic/ship_builder.hpp"

bool addShip(Board* board, Ship* ship, Position shipPosition)
{
    for (short y = 0; y < ship->getSize().first; y++)
        for (short x = 0; x < ship->getSize().second; x++)
            if(!board->canAddShip(Position(y, x) + shipPosition))
                return false;
    board->ships.push_back(ship);
    ship->setIndex((unsigned short)board->ships.size());
    Position shipPos;

    Position lockedPos(shipPosition.y - 1, shipPosition.x - 1);
    Position lockedSize(ship->getSize().first + 2,
                        ship->getSize().second + 2);
    Position lockedSizePos(board->checkBorder(lockedPos.y, lockedSize.y),
                            board->checkBorder(lockedPos.x, lockedSize.x));
    Position cursorPos(board->clamp(lockedPos.y, 0, BOARD_SIZE),
                   board->clamp(lockedPos.x, 0, BOARD_SIZE));

    std::map<Position, Cell> locked;
    for (short y = 0; y < lockedSizePos.y; y++)
        for (short x = 0; x < lockedSizePos.x; x++)
            locked[{y,x}] = Cell(Locked);
    board->drawMap(cursorPos, locked, Water);

    for (short y = 0; y < ship->getSize().first; y++)
    {
        for (short x = 0; x < ship->getSize().second; x++)
        {
            shipPos = shipPosition + Position(y, x);
            board->drawCell(shipPos, Cell(Undamaged), Ships);
            ship->setCell(&board->getLayer(Ships)[shipPos], shipPos);
        }
    }
    board->update();
    return true;
}

void deleteShip(Board* board, unsigned short index)
{
    board->ships.erase(board->ships.begin() + index);
}
