#include "logic/ship.hpp"

Ship::Ship(unsigned short lenght, Board* board)
{
    size = {1, lenght};
    health = lenght;
    gameBoard = board; 
    draw({0, 0});
}

void Ship::rotate() { size = {size.second, size.first}; }

void Ship::draw(Position position)
{
    for (unsigned short y = 0; y < size.first; y++)
        for (unsigned short x = 0; x < size.second; x++)
            gameBoard->drawCell(position + Position(y, x), Cell(Undamaged), UI);
    gameBoard->update();
}

void Ship::takeDamage(Position position)
{
    (*map[position]).updateType(Hit);
    health--;
    // if (health == 0)
    //     gameBoard->deleteShip(index);
}

std::pair<unsigned short, unsigned short> Ship::getSize() { return size; }

std::map<Position, Cell*> Ship::getMap() { return map; }
void Ship::setCell(Cell* cell, Position position) { map[position] = cell; }
void Ship::setIndex(unsigned short index) { this->index = index; }