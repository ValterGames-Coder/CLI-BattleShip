#include "base/ascii.hpp"

void printImage(WINDOW* win, Position position, const char* fileName, unsigned short& numberOfLines, unsigned short color)
{
    std::ifstream file;
    std::string line;
    unsigned short i = 0;
    
    wmove(win, position.y, position.x);
    if (color != 0)
        wattron(win, COLOR_PAIR(color));

    file.open(fileName);
    if (!file.is_open())
        return;

    while (getline(file, line))
    {
        mvwprintw(win, position.y + i, position.x - (line.length() / 2), "%s", line.c_str());
        wrefresh(win);
        i++;
    }
    file.close();
    wattroff(win, COLOR_PAIR(color));
    refresh();
    numberOfLines = i;
}