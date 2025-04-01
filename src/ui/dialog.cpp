#include "ui/dialog.hpp"

Dialog::Dialog(Position dialogPosition, std::wstring text, bool staticSize = false, unsigned short size = 0)
{
    curs_set(0);
    this->dialogPosition = dialogPosition;
    this->staticSize = staticSize;
    this->size = size;
    updateDialog(text);
}

void Dialog::updateDialog(std::wstring text)
{
    if (currentText == text)
        return;
    if (dialogWin != nullptr) 
    {
        wclear(dialogWin);
        wrefresh(dialogWin);
    }
    if (staticSize)
        dialogWin = newwin(3, size + 4, dialogPosition.y, dialogPosition.x - (size / 2) - 1);
    else
        dialogWin = newwin(3, text.length() + 4, dialogPosition.y, dialogPosition.x - (text.length() / 2) - 1);
    box(dialogWin, 0, 0);
    wmove(dialogWin, 1, 2);
#if defined(_WIN32)
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string winTxt = converter.to_bytes(text);
    waddnstr(dialogWin, winTxt.c_str(), winTxt.size());
#else
    waddwstr(dialogWin, text.c_str());
#endif
    wrefresh(dialogWin);
    currentText = text;
}