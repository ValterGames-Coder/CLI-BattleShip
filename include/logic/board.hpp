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
    Ships,
    Water
};

class Ship;

class Board
{
private:
    WINDOW* boardWin;
    std::map<Position, Cell> waterMap;
    std::map<Position, Cell> shipMap;
    std::map<Position, Cell> uiMap;
    unsigned short height, width;
    std::vector<Ship*> ships;
    bool canAddShip(Position position);
    void drawBoard();
    void drawRectangle(Position pos1, Position pos2);
public:
    bool shipsVisable = true;
    Board(Position boardPosition);
    void update();
    void drawCell(Position position, Cell cell, BoardLayer layer);
    void drawMap(std::map<Position, Cell> map, BoardLayer layer);
    bool addShip(Ship* ship, Position shipPosition);
    void deleteShip(unsigned short index);
    std::map<Position, Cell>& getBoard(BoardLayer layer);
    WINDOW* getWindow();
};