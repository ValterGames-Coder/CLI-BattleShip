#pragma once
#include <ncurses.h>
#include <map>
#include <vector>
#include "base/position.hpp"
#include "base/cell.hpp"
#include "logic/ship.hpp"

#define GRID_SIZE 3
#define BOARD_SIZE 10

enum BoardLayer
{
    UI,
    Water
};

class Board
{
private:
    WINDOW* boardWin;
    std::map<const Position, Cell> water;
    std::vector<Ship*> ships;
    //std::map<const Position, Cell> shipMap;
    std::map<const Position, Cell> ui;
    unsigned short height, width;

    void update();
    void drawBoard();
    void drawRectangle(Position pos1, Position pos2);
public:
    bool shipsVisable = true;
    Board(Position boardPosition);
    //bool canAdd(std::map<const Position, Cell> map);
    //bool canAdd(const Position);
    void drawCell(Position position, Cell cell, BoardLayer layer);
    void drawMap(std::map<const Position, Cell> map, BoardLayer layer);
    unsigned short addShip(Ship* ship);
    void deleteShip(unsigned short index);
    std::map<const Position, Cell>& getBoard(BoardLayer layer);
};