#pragma once
#include <string>

enum CellType
{
    Empty,
    Locked,
    Undamaged,
    Hit,
    Missed,
    Aim
};

struct Cell
{
    Cell(CellType type = Empty) { updateType(type); }

    CellType type;
    std::string symbol;
    unsigned color;

    void updateType(CellType type)
    {
        this->type = type;
        switch (this->type)
        {
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
};