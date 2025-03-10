#pragma once
#include <ncurses.h>
#include "base/position.hpp"
#include "base/ascii.hpp"

namespace Animation
{
    void move(WINDOW* win, Position startPosition, Position endPosition, const char* file, double seconds, unsigned short color);
    void playAnimation(WINDOW* win, Position position, const char* dir, unsigned short color);
}