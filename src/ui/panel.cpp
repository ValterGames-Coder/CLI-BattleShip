#include "ui/panel.hpp"
#include <algorithm>

Panel::Panel(Position position, std::vector<std::string> options)
{
    this->options = options;
    optionsSize = (short)this->options.size();
    std::string max_element = *std::max_element(this->options.begin(), this->options.end());
    panelMenu = newwin(optionsSize + 2, max_element.length() + 2, position.y, position.x);
    box(panelMenu, 0, 0);
    refresh();
    wrefresh(panelMenu);
}

unsigned short Panel::getSelectedItem()
{
    keypad(panelMenu, true);
    wchar_t input;
    short select = 0;
    while (1)
    {
        for (unsigned short i = 0; i < optionsSize; i++)
        {
            if (i == select)
                wattron(panelMenu, A_REVERSE);
            mvwprintw(panelMenu, i+1, 1, "%s",this->options[i].c_str());
            wattroff(panelMenu, A_REVERSE);
        }
        input = wgetch(panelMenu);

        switch (input)
        {
        case KEY_UP:
            select--;
            if (select == -1)
                select = 0;
            break;
        case KEY_DOWN:
            select++;
            if (select == optionsSize)
                select = optionsSize - 1;
        default:
            break;
        }

        if (input == 10) 
            break;
    }
    keypad(panelMenu, false);
    return select;
}