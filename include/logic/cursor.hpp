#pragma once
#include <ncurses.h>
#include <map>
#include "logic/board.hpp"

class Cursor
{
private:
    Board* m_board;
    WINDOW* m_boardWin;
public:
    Position position {0, 0};
    Cursor(Board* board);
    void move(Position newPosition);
    void setBoard(Board* board);
    wchar_t readKeyboard();
    void checkCollision(std::pair<unsigned, unsigned> size);
};