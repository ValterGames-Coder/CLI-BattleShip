#pragma once
#include <ncurses.h>
#include <map>
#include "logic/board.hpp"

class Cursor
{
private:
    Board* board;
    WINDOW* boardWin;
public:
    Position cursorPosition {0, 0};
    Cursor(Board* board);
    void move(Position newPosition);
    void setBoard(Board* board);
    wchar_t readKeyboard();
    void checkCollision(std::pair<unsigned short, unsigned short> size);
};