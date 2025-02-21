#include "scenes/game_scene.hpp"
#include "base/ascii.hpp"

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

void GameScene::win()
{
    wclear(sceneWin);
    Position winSize = getSize("./img/win.txt");
    Position winPosition {(short)(yMax / 2 - winSize.y / 2), (short)(xMax / 2 - winSize.x / 2)};
    printImage(sceneWin, winPosition, "./img/win.txt", COLOR_YELLOW);
}

void GameScene::lose()
{
    wclear(sceneWin);
    Position loseSize = getSize("./img/lose.txt");
    Position losePosition {(short)(yMax / 2 - loseSize.y / 2), (short)(xMax / 2 - loseSize.x / 2)};
    printImage(sceneWin, losePosition, "./img/lose.txt", COLOR_RED);
}