#include "scenes/game_scene.hpp"

void GameScene::load()
{
    playerBoard = new Board(Position(
        (yMax / 2) - BOARD_SPACE_Y,
        (xMax / 2) - BOARD_SPACE_X
    ));
    enemyBoard = new Board(Position(
        (yMax / 2) - BOARD_SPACE_Y,
        (xMax / 2) + BOARD_SPACE_X
    ));
    Ship* ship = new Ship(4);
    ship->setBoard(*playerBoard);
    ship->draw({0, 0});
    dialog = new Dialog(Position((yMax / 2) + 5, (xMax / 2)), 
    L"for move: ← → ↑ ↓ | for rotate: r | for set: enter");
    wrefresh(sceneWin);
    refresh();
    getch();
    //dialog->updateDialog(L"Skibidi dop dop");
}