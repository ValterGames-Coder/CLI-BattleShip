#pragma once
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "scenes/main_menu_scene.hpp"
#include "scenes/game_scene.hpp"

class Game
{
private:
    bool isInit = false;
    unsigned short yMax, xMax;
    MainMenuScene* mainMenuScene;
    GameScene* gameScene;

    unsigned short playerShips[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    unsigned short enemyShips[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

    void setupGame();
    void rules();
public:
    Game();
    void run();
};