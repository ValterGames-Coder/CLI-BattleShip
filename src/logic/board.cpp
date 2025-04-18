#include "logic/board.hpp"

short Board::checkBorder(short pos, short size)
{
    if(pos < 0)
        return size + pos;
    else if (pos + size > BOARD_SIZE)
        return size - ((size + pos) % BOARD_SIZE);
    else
        return size;
}

short Board::clamp(short point, short min, short max)
{
    if (point < min)
        return min;
    else if (point > max)
        return max;
    else
        return point;
}

void Board::drawRectangle(Position pos1, Position pos2)
{
    mvwhline(m_boardWin, pos1.y, pos1.x, 0, pos2.x - pos1.x);
    mvwhline(m_boardWin, pos2.y, pos1.x, 0, pos2.x - pos1.x);
    mvwvline(m_boardWin, pos1.y, pos1.x, 0, pos2.y - pos1.y);
    mvwvline(m_boardWin, pos1.y, pos2.x, 0, pos2.y - pos1.y);
    mvwaddch(m_boardWin, pos1.y, pos1.x, ACS_ULCORNER);
    mvwaddch(m_boardWin, pos2.y, pos1.x, ACS_LLCORNER);
    mvwaddch(m_boardWin, pos1.y, pos2.x, ACS_URCORNER);
    mvwaddch(m_boardWin, pos2.y, pos2.x, ACS_LRCORNER);
}

std::map<const Position, Cell>& Board::getLayer(BoardLayer layer)
{
    if (layer == UI)
        return m_uiMap;
    else if (layer == Ships)
        return m_shipMap;
    return m_waterMap;
}

std::vector<Position> Board::getCells(CellType type)
{
    std::vector<Position> positions;
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
            if(getLayer(Water)[{y, x}].type == type)
                positions.push_back(Position(y, x));
    return positions;
}

bool Board::canAddShip(Position position) 
{ 
    return getLayer(Ships).count(position) == 0 && getLayer(Water)[position].type == Empty; 
}

bool Board::canShoot(Position position)
{
    CellType cell;
    if (getLayer(Ships).count(position))
    {
        cell = getLayer(Ships)[position].type;
        return cell == Undamaged;
    }
    else
    {
        cell = getLayer(Water)[position].type;
        return !(cell == Missed);
    }
}

Ship* Board::getShip(Position position)
{
    for (auto& ship : ships)
        if (ship->getMap().count(position))
            return ship;
    return nullptr;
}

void Board::update()
{
    Cell cell;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            BoardLayer layer;
            if (m_uiMap.count({y, x}))
                layer = UI;
            else if(m_shipMap.count({y, x}))
                layer = Ships;
            else
                layer = Water;
            cell = getLayer(layer)[{y, x}];
            if (layer == Ships && !shipsVisible && cell.type == Undamaged)
                cell = Cell(Empty);
            int color = cell.color;
            if (layer == UI && cell.type == Undamaged)
                color = canAddShip({y, x}) ? COLOR_GREEN : COLOR_RED;
            wattron(m_boardWin, COLOR_PAIR(color));
            mvwprintw(m_boardWin, y + 2, x * 2 + 2, "%s", cell.symbol.c_str());
            wattroff(m_boardWin, COLOR_PAIR(color));
        }
    }
    m_uiMap.clear();
    wmove(stdscr, 0 , 0);
    refresh();
    wrefresh(m_boardWin);
}

void Board::drawBoard()
{
    unsigned letter = 0;
    unsigned number = 0;

    for (int gridY = 0; gridY < m_height - 1; gridY++)
    {
        for (int gridX = 0; gridX < m_width - 1; gridX++)
        {
            if (gridY == 0)
            {
                mvwaddch(m_boardWin, 0, (gridX * 2) + 3, '0' + number);
                number++;
            }
            else if (gridY > 1 && gridX == 0)
            {
                mvwaddch(m_boardWin, gridY, 0, 'A' + letter);
                letter++;
            }
            else if (gridY == 1 && gridX == 1)
            {
                drawRectangle({1, 1}, {m_height - 1, m_width - 1});
            }
            else if (gridY > 1 && gridX > 1)
            {
                update(); 
                break;
            }
        }
    }
    refresh();
    wrefresh(m_boardWin);
}


Board::Board(Position boardPosition)
{
    m_height = BOARD_SIZE + 3;
    m_width = BOARD_SIZE * 2 + 3;
    for (short y = 0; y < BOARD_SIZE; y++)
        for (short x = 0; x < BOARD_SIZE; x++)
            getLayer(Water)[{y, x}] = Cell(Empty);
    
    m_boardWin = newwin(m_height, m_width, boardPosition.y - (m_height / 2), boardPosition.x - (m_width / 2));
    drawBoard();
}


void Board::drawCell(Position position, Cell cell, BoardLayer layer)
{
    getLayer(layer)[position] = cell;
}

void Board::drawMap(Position position, std::map<const Position, Cell> map, BoardLayer layer)
{
    for (const auto& element : map)
        getLayer(layer)[position + element.first] = element.second;
    update();
}

WINDOW* Board::getWindow() { return m_boardWin; }