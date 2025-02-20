#include "scenes/main_menu_scene.hpp"

void MainMenuScene::load()
{
    curs_set(0);
    unsigned short logoLines = 0;
    Position logoSize = getSize("./img/logo.txt");
    Position logoPosition {(short)(yMax / 2 - logoSize.y / 2), (short)(xMax / 2 - logoSize.x / 2)};
    printImage(sceneWin, logoPosition, "./img/logo.txt", logoLines, COLOR_CYAN);
    Position panelPosition {(short)(yMax / 2 + logoLines / 2), (short)(xMax / 2 - 7)};
    Panel* panel = new Panel(panelPosition, options);
    selected = panel->getSelectedItem();
}

std::string MainMenuScene::getInput() { return options[selected]; }