#include "scenes/main_menu_scene.hpp"
#include "animation/animator.hpp"

bool MainMenuScene::intro = false;

void MainMenuScene::load()
{
    curs_set(0);
    Position logoSize = getSize("./img/logo.txt");
    Position shipSize = getSize("./img/ship.txt");
    Position logoPosition {(short)(yMax / 2 - logoSize.y / 2 + shipSize.y / 2), (short)(xMax / 2 - logoSize.x / 2)};
    Position startShipPosition {(short)(yMax / 2 - shipSize.y / 2 - logoSize.y / 2), (short)(xMax - shipSize.x)};
    Position endShipPosition {(short)(yMax / 2 - shipSize.y / 2 - logoSize.y / 2), (short)(xMax / 2 - shipSize.x / 2)};
    
    if (intro == false)
    {
        Animation::move(sceneWin, startShipPosition, endShipPosition, "./img/ship.txt", 1, COLOR_CYAN);
        intro = true;
    }
    else
        printImage(sceneWin, endShipPosition - Position(1, 0), "./img/ship.txt", COLOR_CYAN);
    printImage(sceneWin, logoPosition, "./img/logo.txt", COLOR_CYAN);
    //printf("Ship count here is %i and %i df-!d,{}{SScf}sdouty");
    Position panelPosition {(short)(yMax / 2 + (logoSize.y + shipSize.y) / 2), (short)((xMax / 2) - 2)};
    Panel* panel = new Panel(panelPosition, options);
    selected = panel->getSelectedItem();
}

std::string MainMenuScene::getInput() { return options[selected]; }