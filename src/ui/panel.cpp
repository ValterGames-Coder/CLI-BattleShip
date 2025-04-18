#include "ui/panel.hpp"
#include <algorithm>

Panel::Panel(Position position, std::vector<std::string> options)
{
    m_options = options;
    m_optionsSize = m_options.size();
    std::string max_element = "";
    for (auto& option : m_options)
        if (option.length() > max_element.length())
            max_element = option;
    m_panelMenu = newwin(m_optionsSize + 2, max_element.size() + 2, position.y, position.x - max_element.length() / 2);
    box(m_panelMenu, 0, 0);
    refresh();
    wrefresh(m_panelMenu);
}

unsigned Panel::getSelectedItem()
{
    keypad(m_panelMenu, true);
    wchar_t input;
    unsigned select = 0;
    while (1)
    {
        for (int i = 0; i < m_optionsSize; i++)
        {
            if (i == select)
                wattron(m_panelMenu, A_REVERSE);
            mvwprintw(m_panelMenu, i+1, 1, "%s", m_options[i].c_str());
            wattroff(m_panelMenu, A_REVERSE);
        }
        input = wgetch(m_panelMenu);

        switch (input)
        {
        case KEY_UP:
            select--;
            if (select == -1)
                select = 0;
            break;
        case KEY_DOWN:
            select++;
            if (select == m_optionsSize)
                select = m_optionsSize - 1;
        default:
            break;
        }

        if (input == 10) 
            break;
    }
    keypad(m_panelMenu, false);
    return select;
}