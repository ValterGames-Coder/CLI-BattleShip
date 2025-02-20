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
    Dialog(Position dialogPosition, std::wstring text, bool staticSize, unsigned short size);
    void updateDialog(std::wstring text);
    std::wstring currentText;
    bool staticSize;
    unsigned short size;
};