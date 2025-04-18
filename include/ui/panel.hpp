#pragma once
#include <string>
#include <vector>
#include <ncurses.h>
#include "base/position.hpp"

class Panel
{
private:
    WINDOW* m_panelMenu;
    std::vector<std::string> m_options;
    unsigned m_optionsSize;
public:
    Panel(Position position, std::vector<std::string> options);
    unsigned getSelectedItem();
};