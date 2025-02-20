#include "scenes/rules_scene.hpp"
#include "base/ascii.hpp"

void RulesScene::load()
{
    curs_set(0);
    unsigned short logoLines = 0;
     //   printImage(stdscr, Position(yMax / 2 - 3, xMax / 2), "./img/win.txt", logoLines, COLOR_YELLOW);
    Position ruleSize = getSize("./img/rules.txt");
    Position rulePosition {(short)(yMax / 2 - ruleSize.y / 2), (short)(xMax / 2 - ruleSize.x / 2)};
    printImage(sceneWin, rulePosition, "./img/rules.txt", logoLines, COLOR_WHITE);
    getch();
}