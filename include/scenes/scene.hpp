#pragma once
#include <ncurses.h>

class Scene
{
protected:
    unsigned short xMax, yMax;
    WINDOW* sceneWin;
public:
    inline Scene();
    virtual inline void load();
};