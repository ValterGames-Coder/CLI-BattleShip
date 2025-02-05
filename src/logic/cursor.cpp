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
        cursorPosition.y--;
        if (cursorPosition.y < 0)
            cursorPosition.y = 0;
        break;
    case KEY_DOWN:
        cursorPosition.y++;
        if (cursorPosition.y > BOARD_SIZE)
            cursorPosition.y = BOARD_SIZE;
        break;
    case KEY_LEFT:
        cursorPosition.x--;
        if (cursorPosition.x < 0)
            cursorPosition.x = 0;
        break;
    case KEY_RIGHT:
        cursorPosition.x++;
        if (cursorPosition.x > BOARD_SIZE)
            cursorPosition.x = BOARD_SIZE;
        break;
    default:
        break;
    }
    return input;
}