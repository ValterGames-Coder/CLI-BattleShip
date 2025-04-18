#pragma once
#include <ncurses.h>
#include <map>
#include "logic/board.hpp"
#include "base/position.hpp"
#include "base/cell.hpp"

class Board;

class Ship
{
private:
    Board* m_gameBoard;
    std::pair<unsigned, unsigned> m_size;
    unsigned m_health;
    std::map<const Position, Cell*> m_map;
public:
    bool isDestroyed;
    Ship(unsigned lenght, Board* board);
    Position cursorPosition;
    std::map<const Position, Cell> locked;
    void rotate();
    void draw(Position position);
    void takeDamage(Position position);
    std::pair<unsigned, unsigned> getSize();
    std::map<const Position, Cell*> getMap();
    void setCell(Cell* cell, Position position);
};