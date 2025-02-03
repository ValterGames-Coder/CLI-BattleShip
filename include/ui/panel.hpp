#pragma once
#include <string>
#include <vector>
#include <ncurses.h>
#include "base/position.hpp"

class Panel
{
private:
    WINDOW* panelMenu;
    std::vector<std::string> options;
    unsigned short optionsSize;
public:
    Panel(Position position, std::vector<std::string> options);
    unsigned short getSelectedItem();
};