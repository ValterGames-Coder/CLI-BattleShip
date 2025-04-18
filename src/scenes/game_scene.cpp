#include "scenes/game_scene.hpp"
#include "base/ascii.hpp"

GameScene::GameScene(): Scene() { load(); }

void GameScene::load()
{
    curs_set(0);
    playerBoard = new Board(Position(
        (yMax / 2) - BOARD_SPACE_Y,
        (xMax / 2) - BOARD_SPACE_X
    ));
    enemyBoard = new Board(Position(
        (yMax / 2) - BOARD_SPACE_Y,
        (xMax / 2) + BOARD_SPACE_X
    ));
    wrefresh(sceneWin);
    refresh();
}

void GameScene::endMenu(const char* file, unsigned color)
{
    wclear(sceneWin);
    Position fileSize = getSize(file);
    Position winPosition {yMax / 2 - fileSize.y / 2, xMax / 2 - fileSize.x / 2};
    printImage(sceneWin, winPosition, file, color);
}