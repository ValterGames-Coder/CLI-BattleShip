#include "logic/cursor.hpp"

void Cursor::setBoard(Board* board)
{
    this->board = board;
    boardWin = board->getWindow();
}

Cursor::Cursor(Board* board) { setBoard(board); }

void Cursor::move(Position newPosition)
{
    cursorPosition = newPosition;
    wmove(boardWin, cursorPosition.y + 2, cursorPosition.x * 2 + 2);
}

wchar_t Cursor::readKeyboard()
{
    keypad(boardWin, true);
    wchar_t input;
    input = wgetch(boardWin);
    switch (input)
    {
    case KEY_UP:
        /* code */
        break;
    
    default:
        break;
    }
}