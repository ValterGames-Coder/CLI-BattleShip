#include "scenes/game_scene.hpp"

void GameScene::load()
{
    Ship* ship = new Ship(4, *playerBoard);
    playerBoard = new Board(Position(
        (yMax / 2) - BOARD_SPACE_Y,
        (xMax / 2) - BOARD_SPACE_X
    ));
    enemyBoard = new Board(Position(
        (yMax / 2) - BOARD_SPACE_Y,
        (xMax / 2) + BOARD_SPACE_X
    ));
    ship->draw({0, 0});
    dialog = new Dialog(Position((yMax / 2) + 5, (xMax / 2)), 
    L"for move: ← → ↑ ↓ | for rotate: r | for set: enter");
    wrefresh(sceneWin);
    refresh();
    getch();
    //dialog->updateDialog(L"Skibidi dop dop");
}