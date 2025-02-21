#include "scenes/main_menu_scene.hpp"
#include "animation/animator.hpp"

void MainMenuScene::load()
{
    curs_set(0);
    Position logoSize = getSize("./img/logo.txt");
    Position shipSize = getSize("./img/ship.txt");
    Position logoPosition {(short)(yMax / 2 - logoSize.y / 2 + shipSize.y / 2), (short)(xMax / 2 - logoSize.x / 2)};
    Position startShipPosition {(short)(yMax / 2 - shipSize.y / 2 - logoSize.y / 2), (short)(xMax - shipSize.x)};
    Position endShipPosition {(short)(yMax / 2 - shipSize.y / 2 - logoSize.y / 2), (short)(xMax / 2 - shipSize.x / 2)};
    
    Animation::move(sceneWin, startShipPosition, endShipPosition, "./img/ship.txt", 2, COLOR_CYAN);
    printImage(sceneWin, logoPosition, "./img/logo.txt", COLOR_CYAN);
    
    Position panelPosition {(short)(yMax / 2 + (logoSize.y + shipSize.y) / 2), (short)(xMax / 2 - 7)};
    Panel* panel = new Panel(panelPosition, options);
    selected = panel->getSelectedItem();
}

std::string MainMenuScene::getInput() { return options[selected]; }