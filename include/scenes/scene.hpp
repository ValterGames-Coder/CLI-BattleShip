#pragma once
#include <ncurses.h>

class Scene
{
protected:
    unsigned xMax, yMax;
    WINDOW* sceneWin;
public:
    Scene();
    virtual void load() = 0;
};