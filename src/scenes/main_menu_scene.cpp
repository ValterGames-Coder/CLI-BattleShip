#include "scenes/main_menu_scene.hpp"

void MainMenuScene::load()
{
    curs_set(0);
    unsigned short logoLines = 0;
    Position logoPosition {(short)(yMax / 2 - 7), (short)(xMax / 2)};
    printImage(sceneWin, logoPosition, "./img/logo.txt", logoLines, COLOR_CYAN);
    Position panelPosition {(short)(yMax / 2 + logoLines / 1.5), (short)(xMax / 2 - 7)};
    Panel* panel = new Panel(panelPosition, options);
    selected = panel->getSelectedItem();
}

std::string MainMenuScene::getInput() { return options[selected]; }