#include "logic/cursor.hpp"

void Cursor::setBoard(Board* board)
{
    m_board = board;
    m_boardWin = board->getWindow();
}

Cursor::Cursor(Board* board) { setBoard(board); }

void Cursor::move(Position newPosition)
{
    position = newPosition;
    wmove(m_boardWin, position.y + 2, position.x * 2 + 2);
}

wchar_t Cursor::readKeyboard()
{
    keypad(m_boardWin, true);
    wchar_t input;
    input = wgetch(m_boardWin);
    switch (input)
    {
    case KEY_UP:
        position.y--;
        if (position.y < 0)
            position.y = 0;
        break;
    case KEY_DOWN:
        position.y++;
        if (position.y > BOARD_SIZE)
            position.y = BOARD_SIZE;
        break;
    case KEY_LEFT:
        position.x--;
        if (position.x < 0)
            position.x = 0;
        break;
    case KEY_RIGHT:
        position.x++;
        if (position.x > BOARD_SIZE)
            position.x = BOARD_SIZE;
        break;
    default:
        break;
    }
    move(position);
    return input;
}

void Cursor::checkCollision(std::pair<unsigned, unsigned> size)
{
    if (position.y + size.first > BOARD_SIZE)
        move(Position(BOARD_SIZE - size.first, position.x));
    if (position.x + size.second > BOARD_SIZE)
        move(Position(position.y, BOARD_SIZE - size.second));
}