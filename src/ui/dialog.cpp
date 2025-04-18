#include "ui/dialog.hpp"

Dialog::Dialog(Position dialogPosition, std::wstring text, bool staticSize = false, unsigned size = 0)
{
    curs_set(0);
    m_dialogPosition = dialogPosition;
    this->staticSize = staticSize;
    this->size = size;
    updateDialog(text);
}

void Dialog::updateDialog(std::wstring text)
{
    if (currentText == text)
        return;
    if (m_dialogWin != nullptr) 
    {
        wclear(m_dialogWin);
        wrefresh(m_dialogWin);
    }
    if (staticSize)
        m_dialogWin = newwin(3, size + 4, m_dialogPosition.y, m_dialogPosition.x - (size / 2) - 1);
    else
        m_dialogWin = newwin(3, text.length() + 4, m_dialogPosition.y, m_dialogPosition.x - (text.length() / 2) - 1);
    box(m_dialogWin, 0, 0);
    wmove(m_dialogWin, 1, 2);
#if defined(_WIN32)
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string winTxt = converter.to_bytes(text);
    waddnstr(m_dialogWin, winTxt.c_str(), winTxt.size());
#else
    waddwstr(m_dialogWin, text.c_str());
#endif
    wrefresh(m_dialogWin);
    currentText = text;
}