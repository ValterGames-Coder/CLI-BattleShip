#pragma once
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "scenes/main_menu_scene.hpp"
#include "scenes/game_scene.hpp"
#include "scenes/rules_scene.hpp"
#include "logic/bot.hpp"

class Cursor;

enum GameState
{
    Setup,
    Play,
    Win,
    Lose
};

class Game
{
private:
    bool isInit = false;
    unsigned short yMax, xMax;
    MainMenuScene* mainMenuScene;
    GameScene* gameScene;
    RulesScene* rulesScene;
    GameState state = Setup;

    unsigned short playerShips[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    unsigned short enemyShips[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

    void startGame();
    void setupPlayerShips(Cursor* cursor);
    void setupEnemyShips(Board* enemyBoard);
    void gameLoop(Cursor* cursor, Board* enemyBoard, Bot* bot);
    void updateDialogs();
    void checkState();
    void rules();
public:
    Game();
    void run();
};