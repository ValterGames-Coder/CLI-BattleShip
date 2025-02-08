#include "logic/board.hpp"

void Board::drawRectangle(Position pos1, Position pos2)
{
    mvwhline(boardWin, pos1.y, pos1.x, 0, pos2.x - pos1.x);
    mvwhline(boardWin, pos2.y, pos1.x, 0, pos2.x - pos1.x);
    mvwvline(boardWin, pos1.y, pos1.x, 0, pos2.y - pos1.y);
    mvwvline(boardWin, pos1.y, pos2.x, 0, pos2.y - pos1.y);
    mvwaddch(boardWin, pos1.y, pos1.x, ACS_ULCORNER);
    mvwaddch(boardWin, pos2.y, pos1.x, ACS_LLCORNER);
    mvwaddch(boardWin, pos1.y, pos2.x, ACS_URCORNER);
    mvwaddch(boardWin, pos2.y, pos2.x, ACS_LRCORNER);
}

std::map<Position, Cell>& Board::getBoard(BoardLayer layer)
{
    switch (layer)
    {
    case UI:
        return uiMap;
    case Ships:
        return shipMap;
    case Water:
        return waterMap;
    default:
        break;
    }
    return waterMap;
}

bool Board::canAddShip(Position position) { return shipMap.count(position) == 0; }

void Board::update()
{
    for (short y = 0; y < BOARD_SIZE; y++)
    {
        for (short x = 0; x < BOARD_SIZE; x++)
        {
            BoardLayer layer;
            if (uiMap.count({y, x}))
                layer = UI;
            else if(shipMap.count({y, x}))
                layer = Ships;
            else
                layer = Water;
            
            Cell cell = getBoard(layer)[{y, x}];
            if (layer == Ships && !shipsVisable && cell.type == Undamaged)
                cell = Cell(Empty);
            int color = cell.color;
            if (layer == UI && cell.type == Undamaged)
                color = canAddShip({y, x}) ? COLOR_GREEN : COLOR_RED;
            wattron(boardWin, COLOR_PAIR(color));
            mvwprintw(boardWin, y + 2, x * 2 + 2, "%s", cell.symbol.c_str());
            wattroff(boardWin, COLOR_PAIR(color));
        }
    }
    // for (short y = 0; y < BOARD_SIZE; y++)
    // {
    //     for (short x = 0; x < BOARD_SIZE; x++)
    //     {
    //         Cell cell = getBoard(Water)[{y, x}];
    //         // if (layer == Ships && !shipsVisable && cell.type == Undamaged)
    //         //     cell = Cell(Empty);
    //         int color = cell.color;
    //         // if (cell.type == Undamaged)
    //         //     color = canAddShip({y, x}) ? COLOR_GREEN : COLOR_RED;
    //         wattron(boardWin, COLOR_PAIR(color));
    //         mvwprintw(boardWin, y + 2, x * 2 + 2, "%s", cell.symbol.c_str());
    //         wattroff(boardWin, COLOR_PAIR(color));
    //     }
    // }

    // for (auto pair : getBoard(Ships))
    // {
    //     int color = pair.second.color;
    //     // if (cell.type == Undamaged)
    //     //     color = canAddShip({y, x}) ? COLOR_GREEN : COLOR_RED;
    //     wattron(boardWin, COLOR_PAIR(color));
    //     mvwprintw(boardWin, pair.first.y + 2, pair.first.x * 2 + 2, "%s", pair.second.symbol.c_str());
    //     wattroff(boardWin, COLOR_PAIR(color));
    // }

    // for (auto pair : getBoard(Ships))
    // {
    //     int color = pair.second.color;
    //     if (pair.second.type == Undamaged)
    //         color = canAddShip(pair.first) ? COLOR_GREEN : COLOR_RED;
    //     // if (cell.type == Undamaged)
    //     //     color = canAddShip({y, x}) ? COLOR_GREEN : COLOR_RED;
    //     wattron(boardWin, COLOR_PAIR(color));
    //     mvwprintw(boardWin, pair.first.y + 2, pair.first.x * 2 + 2, "%s", pair.second.symbol.c_str());
    //     wattroff(boardWin, COLOR_PAIR(color));
    // }

    // // for (short y = 0; y < BOARD_SIZE; y++)
    // // {
    // //     for (short x = 0; x < BOARD_SIZE; x++)
    // //     {
    // //         if (getBoard(Ships).count({y, x}) == 0)
    // //             continue;
    // //         Cell cell = getBoard(Ships)[{y, x}];
    // //         // if (layer == Ships && !shipsVisable && cell.type == Undamaged)
    // //         //     cell = Cell(Empty);
    // //         int color = cell.color;
    // //         // if (cell.type == Undamaged)
    // //         //     color = canAddShip({y, x}) ? COLOR_GREEN : COLOR_RED;
    // //         wattron(boardWin, COLOR_PAIR(color));
    // //         mvwprintw(boardWin, y + 2, x * 2 + 2, "%s", cell.symbol.c_str());
    // //         wattroff(boardWin, COLOR_PAIR(color));
    // //     }
    // // }

    // for (short y = 0; y < BOARD_SIZE; y++)
    // {
    //     for (short x = 0; x < BOARD_SIZE; x++)
    //     {
    //         if (getBoard(UI).count({y, x}) == 0)
    //             continue;
    //         Cell cell = getBoard(UI)[{y, x}];
    //         // if (layer == Ships && !shipsVisable && cell.type == Undamaged)
    //         //     cell = Cell(Empty);
    //         int color = cell.color;
    //         if (cell.type == Undamaged)
    //             color = canAddShip({y, x}) ? COLOR_GREEN : COLOR_RED;
    //         wattron(boardWin, COLOR_PAIR(color));
    //         mvwprintw(boardWin, y + 2, x * 2 + 2, "%s", cell.symbol.c_str());
    //         wattroff(boardWin, COLOR_PAIR(color));
    //     }
    // }
    uiMap.clear();
    refresh();
    wrefresh(boardWin);
}

void Board::drawBoard()
{
    short letter = 0;
    short number = 0;

    for (unsigned short gridY = 0; gridY < height - 1; gridY++)
    {
        for (unsigned short gridX = 0; gridX < width - 1; gridX++)
        {
            if (gridY == 0)
            {
                mvwaddch(boardWin, 0, (gridX * 2) + 3, '0' + number);
                number++;
            }
            else if (gridY > 1 && gridX == 0)
            {
                mvwaddch(boardWin, gridY, 0, 'A' + letter);
                letter++;
            }
            else if (gridY == 1 && gridX == 1)
            {
                drawRectangle({1, 1}, {(short)(height - 1), (short)(width - 1)});
            }
            else if (gridY > 1 && gridX > 1)
            {
                update(); 
                break;
            }
        }
    }
    refresh();
    wrefresh(boardWin);
}


Board::Board(Position boardPosition)
{
    height = BOARD_SIZE + 3;
    width = BOARD_SIZE * 2 + 3;
    for (short y = 0; y < BOARD_SIZE; y++)
        for (short x = 0; x < BOARD_SIZE; x++)
            waterMap[{y, x}] = Cell(Empty);
    
    boardWin = newwin(height, width, boardPosition.y - (height / 2), boardPosition.x - (width / 2));
    drawBoard();
}


void Board::drawCell(Position position, Cell cell, BoardLayer layer)
{
    getBoard(layer)[position] = cell;
}

void Board::drawMap(std::map<Position, Cell> map, BoardLayer layer)
{
    for (const auto& element : map)
        getBoard(layer)[element.first] = element.second;
    update();
}

void Board::deleteShip(unsigned short index)
{
    ships.erase(ships.begin() + index);
}

bool Board::addShip(Ship* ship, Position shipPosition)
{
    for (short y = 0; y < ship->getSize().first; y++)
        for (short x = 0; x < ship->getSize().second; x++)
            if(!canAddShip(Position{y, x} + shipPosition))
                return false;
    //ships.push_back(ship);
    //ship->setIndex((unsigned short)ships.size());
    Position shipPos;
    for (unsigned short y = 0; y < ship->getSize().first; y++)
    {
        for (unsigned short x = 0; x < ship->getSize().second; x++)
        {
            shipPos = shipPosition + Position(y, x);
            drawCell(shipPos, Cell(Undamaged), Ships);
            //ship->setCell(&shipMap[shipPos], shipPos);
        }
    }
    update();
    return true;
}

WINDOW* Board::getWindow() { return boardWin; }