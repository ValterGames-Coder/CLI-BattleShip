#pragma once
#include <codecvt>
#include <ncurses.h>
#include <string>
#include "base/position.hpp"

class Dialog
{
private:
    WINDOW* m_dialogWin = nullptr;
    Position m_dialogPosition;
public:
    Dialog(Position dialogPosition, std::wstring text, bool staticSize, unsigned size);
    void updateDialog(std::wstring text);
    std::wstring currentText;
    bool staticSize;
    unsigned size;
};