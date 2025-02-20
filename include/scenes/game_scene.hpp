#pragma once
#include <ncurses.h>
#include "scenes/scene.hpp"
#include "ui/dialog.hpp"
#include "logic/board.hpp"

#define BOARD_SIZE 10
#define BOARD_SPACE_X (BOARD_SIZE + 4)
#define BOARD_SPACE_Y (BOARD_SIZE / 3)

class GameScene : public Scene
{
public:
    void load() override;
    void win();
    void lose();

    Board* playerBoard;
    Board* enemyBoard;
    Dialog* playerShipsDialog = nullptr;
    Dialog* enemyShipsDialog = nullptr;
};