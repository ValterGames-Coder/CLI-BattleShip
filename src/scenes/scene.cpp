#include "scenes/scene.hpp"

Scene::Scene()
{
    erase();
    getmaxyx(stdscr, yMax, xMax);
    sceneWin = newwin(yMax, xMax, 0, 0);
    refresh();
    wrefresh(sceneWin);
}