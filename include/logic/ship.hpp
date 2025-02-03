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
    std::map<Position, Cell*> map;
    unsigned short health;
    unsigned short index;
public:
    Ship(unsigned short lenght, Board* board);
    void rotate();
    void draw(Position position);
    //void setup(Position position);
    void takeDamage(Position position);
};