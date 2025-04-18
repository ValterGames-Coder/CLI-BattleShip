#pragma once
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "scenes/scene.hpp"
#include "logic/cursor.hpp"
#include "logic/ship_builder.hpp"
#include "logic/shooter.hpp"
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

enum GameType
{
    PlayerVSPlayer,
    PlayerVSBot
};

class Game
{
private:
    bool _isInit = false;
    unsigned short _yMax, _xMax;
    MainMenuScene* _mainMenuScene = nullptr;
    GameScene* _gameScene = nullptr;
    RulesScene* _rulesScene = nullptr;
    GameState _state = Setup;
    GameType _gameType = PlayerVSBot;

    unsigned short _playerShips[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    unsigned short _enemyShips[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

    void startGame();
    void setupPlayerShips(Cursor* cursor, Board* board);
    void setupEnemyShips(Board* enemyBoard);
    void gameLoop(Cursor* cursor, Board* playerBoard, Board* enemyBoard, Bot* bot = nullptr);
    void updateDialog(Board* board, Dialog* dialog, short multiply);
    void checkGameState();
    void rules();
public:
    Game();
    void run();
};