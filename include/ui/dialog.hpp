#pragma once
#include <ncurses.h>
#include <string>
#include "base/position.hpp"

class Dialog
{
private:
    WINDOW* dialogWin = nullptr;
    Position dialogPosition;
public:
    Dialog(Position dialogPosition, std::wstring text);
    void updateDialog(std::wstring text);
};