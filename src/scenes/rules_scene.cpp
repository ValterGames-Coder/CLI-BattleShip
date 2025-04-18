#include "scenes/rules_scene.hpp"
#include "base/ascii.hpp"

RulesScene::RulesScene(): Scene() { load(); }

void RulesScene::load()
{
    curs_set(0);
    Position ruleSize = getSize("./img/rules.txt");
    Position rulePosition {yMax / 2 - ruleSize.y / 2, xMax / 2 - ruleSize.x / 2};
    printImage(sceneWin, rulePosition, "./img/rules.txt", COLOR_WHITE);
    getch();
}