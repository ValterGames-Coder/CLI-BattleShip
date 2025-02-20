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
    Board* gameBoard;
    std::pair<unsigned short, unsigned short> size;
    unsigned short health;
    unsigned short index;
    std::map<const Position, Cell*> map;
public:
    bool isDestroyed;
    Ship(unsigned short lenght, Board* board);
    Position cursorPosition;
    std::map<const Position, Cell> locked;
    void rotate();
    void draw(Position position);
    void takeDamage(Position position);
    std::pair<unsigned short, unsigned short> getSize();
    std::map<const Position, Cell*> getMap();
    void setCell(Cell* cell, Position position);
    void setIndex(unsigned short index);
};