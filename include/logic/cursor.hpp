#pragma once
#include <ncurses.h>
#include "logic/board.hpp"

class Cursor
{
private:
    Board* board;
    WINDOW* boardWin;
    void move(Position newPosition);
public:
    Position cursorPosition {0, 0};
    Cursor(Board* board);
    void setBoard(Board* board);
    wchar_t readKeyboard();
};