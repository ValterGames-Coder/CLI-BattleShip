#include "base/ascii.hpp"

Position getSize(const char* fileName)
{
    std::wifstream file;
    std::wstring line;
    int widht = 0, height = 0;
    file.open(fileName);
    if (!file.is_open())
        throw "File isn't open";

    while (getline(file, line))
    {
        height++;
        if (widht < line.size())
            widht = line.size();
    }
    return {height, widht};
}

void printImage(WINDOW* win, Position position, const char* fileName, unsigned color)
{
    std::wifstream file;
    std::wstring line;
    unsigned i = 0;
    std::vector<std::wstring> inputVector;
    
    wmove(win, position.y, position.x);
    if (color != 0)
        wattron(win, COLOR_PAIR(color));

    file.open(fileName);
    if (!file.is_open())
        throw "File isn't open";

    while (getline(file, line))
    {
        mvwprintw(win, position.y + i, position.x, "%ls", line.c_str());
        wrefresh(win);
        i++;
    }
    file.close();
    wattroff(win, COLOR_PAIR(color));
    refresh();
}