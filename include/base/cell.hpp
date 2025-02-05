#pragma once
#include <string>

enum CellType
{
    None,
    Empty,
    Locked,
    Undamaged,
    Hit,
    Missed,
    Aim
};

struct Cell
{
    Cell(CellType type = Empty)
    { 
        this->type = type;
        switch (this->type)
        {
        case None:
            symbol = " .";
            color = COLOR_BLUE;
            break;
        case Empty:
            symbol = " .";
            color = COLOR_BLUE;
            break;
        case Locked:
            symbol = " .";
            color = COLOR_BLUE;
            break;
        case Undamaged:
            symbol = "[]";
            color = COLOR_WHITE;
            break;
        case Hit:
            symbol = "XX";
            color = COLOR_RED;
            break;
        case Missed:
            symbol = "##";
            color = COLOR_BLUE;
            break;
        case Aim:
            symbol = "()";
            color = COLOR_YELLOW;
            break;
        default:
            break;
        }
    }

    CellType type;
    std::string symbol;
    unsigned short color;
};