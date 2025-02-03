#include "logic/ship.hpp"

Ship::Ship(unsigned short lenght, Board* board)
{
    size = {1, lenght};
    health = lenght;
    gameBoard = board; 
}

void Ship::rotate()
{
    std::pair<unsigned short, unsigned short> buffer = {size.second, size.first};
    size = buffer;
}

void Ship::draw(Position position)
{
    for (unsigned short y = 0; y < size.first; y++)
        for (unsigned short x = 0; x < size.second; x++)
            gameBoard->drawCell(position + Position(y, x), Cell(Undamaged), UI);
}

// void Ship::setup(Position position)
// {
//     for (unsigned short y = 0; y < size.first; y++)
//     {
//         for (unsigned short x = 0; x < size.second; x++)
//         {
//             index = gameBoard->addShip(this);
//         }
//     }
// }

void Ship::takeDamage(Position position)
{
    (*map[position]) = Cell(Hit);
    health--;
    if (health == 0)
        gameBoard->deleteShip(index);
}