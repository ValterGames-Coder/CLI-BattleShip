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
    // dialog = new Dialog(Position((yMax / 2) + 5, (xMax / 2)), 
    // L"for move: ← → ↑ ↓ | for rotate: r | for set: enter");
    wrefresh(sceneWin);
    refresh();
}

void GameScene::endMenu(const char* file, unsigned short color)
{
    wclear(sceneWin);
    Position fileSize = getSize(file);
    Position winPosition {(short)(yMax / 2 - fileSize.y / 2), (short)(xMax / 2 - fileSize.x / 2)};
    printImage(sceneWin, winPosition, file, color);
}