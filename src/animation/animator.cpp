#include "animation/animator.hpp"

namespace Animation
{
    void move(WINDOW* win, Position startPosition, Position endPosition, const char* file, double seconds, unsigned color)
    {
        Position currentPosition;
        double t = 0;
        while (t / seconds < 1)
        {
            wclear(win);
            currentPosition = startPosition * (1 - t / seconds) + endPosition * (t / seconds);
            printImage(win, currentPosition, file, color);
            t += 0.1;
            napms(100);
        }
    }
}