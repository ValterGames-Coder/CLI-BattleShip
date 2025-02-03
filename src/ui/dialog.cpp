#include "ui/dialog.hpp"

Dialog::Dialog(Position dialogPosition, std::wstring text)
{
    curs_set(0);
    this->dialogPosition = dialogPosition;
    updateDialog(text);
}

void Dialog::updateDialog(std::wstring text)
{
    if (dialogWin != nullptr) 
    {
        wclear(dialogWin);
        wrefresh(dialogWin);
    }
    dialogWin = newwin(3, text.length() + 4, dialogPosition.y, dialogPosition.x - (text.length() / 2) - 1);
    box(dialogWin, 0, 0);
    wmove(dialogWin, 1, 2);
    waddwstr(dialogWin, text.c_str());
    wrefresh(dialogWin);
    refresh();
}