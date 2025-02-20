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
    std::map<const Position, Cell> waterMap;
    std::map<const Position, Cell> shipMap;
    std::map<const Position, Cell> uiMap;
    unsigned short height, width;
    void drawBoard();
    void drawRectangle(Position pos1, Position pos2);
public:
    std::vector<Ship*> ships;
    std::vector<Position> getCells(CellType type);
    bool shipsVisable = true;
    short checkBorder(short pos, short size);
    short clamp(short point, short min, short max);
    bool canShoot(Position position);
    bool canAddShip(Position position);
    Ship* getShip(Position position);
    Board(Position boardPosition);
    void update();
    void drawCell(Position position, Cell cell, BoardLayer layer);
    void drawMap(Position position, std::map<const Position, Cell> map, BoardLayer layer);
    std::map<const Position, Cell>& getLayer(BoardLayer layer);
    WINDOW* getWindow();
};