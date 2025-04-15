#pragma once
#include "scenes/scene.hpp"
#include "base/position.hpp"
#include "base/ascii.hpp"
#include "ui/panel.hpp"
#include <vector>
#include <string>

class MainMenuScene : public Scene
{
private:
    static bool intro;
    unsigned short selected = 0;
    std::vector<std::string> options {"Player vs Player", "Player vs Bot", "Rules", "Exit"};
public:
    MainMenuScene();
    void load() override;
    std::string getInput();
};
