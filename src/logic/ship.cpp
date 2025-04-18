#include "logic/ship.hpp"
#include "logic/ship_builder.hpp"

Ship::Ship(unsigned lenght, Board* board)
{
    m_size = {1, lenght};
    m_health = lenght;
    m_gameBoard = board; 
    draw({0, 0});
}

void Ship::draw(Position position)
{
    for (int y = 0; y < m_size.first; y++)
        for (int x = 0; x < m_size.second; x++)
        m_gameBoard->drawCell(position + Position(y, x), Cell(Undamaged), UI);
    m_gameBoard->update();
}

void Ship::takeDamage(Position position)
{
    if (isDestroyed)
        return;
    (*m_map[position]).updateType(Hit);
    m_health--;
    if (m_health == 0)
    {
        isDestroyed = true;
        deleteShip(m_gameBoard, position);
    }
}

void Ship::rotate() { m_size = {m_size.second, m_size.first}; }
std::pair<unsigned, unsigned> Ship::getSize() { return m_size; }
std::map<const Position, Cell*> Ship::getMap() { return m_map; }
void Ship::setCell(Cell* cell, Position position) { m_map[position] = cell; }