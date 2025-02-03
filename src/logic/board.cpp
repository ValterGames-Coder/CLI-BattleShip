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

void Board::update()
{
    for (short y = 0; y < BOARD_SIZE; y++)
    {
        for (short x = 0; x < BOARD_SIZE; x++)
        {
            Cell cell = water[{y, x}];
            if (!shipsVisable && water[{y, x}].type == Undamaged)
                cell = Cell(Empty);
            int color = cell.color;
            wattron(boardWin, COLOR_PAIR(color));
            mvwprintw(boardWin, y + 2, x * 2 + 2, "%s", cell.symbol.c_str());
            wattroff(boardWin, COLOR_PAIR(color));
        }
    }

    refresh();
    wrefresh(boardWin);
}

void Board::drawBoard()
{
    short letter = 0;
    short number = 0;

    for (short gridY = 0; gridY < height - 1; gridY++)
    {
        for (short gridX = 0; gridX < width - 1; gridX++)
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
    {
        for (short x = 0; x < BOARD_SIZE; x++)
        {
            water[{y, x}] = Cell(Empty);
            ui[{y, x}] = Cell(None);
        }
    }
    boardWin = newwin(height, width, boardPosition.y - (height / 2), boardPosition.x - (width / 2));
    drawBoard();
}

std::map<const Position, Cell>& Board::getBoard(BoardLayer layer)
{
    switch (layer)
    {
    case UI:
        return ui;
    case Water:
        return water;
    default:
        break;
    }
    return water;
}

void Board::drawCell(Position position, Cell cell, BoardLayer layer)
{
    getBoard(layer)[position] = cell;
    update();
}

void Board::drawMap(std::map<const Position, Cell> map, BoardLayer layer)
{
    for (const auto& element : map)
        getBoard(layer)[element.first] = element.second;
    update();
}

void Board::deleteShip(unsigned short index)
{
    ships.erase(ships.begin() + index);
}

unsigned short Board::addShip(Ship* ship)
{
    ships.push_back(ship);
    return (unsigned short)ships.size();
}