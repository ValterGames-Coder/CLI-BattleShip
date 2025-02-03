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
    unsigned short selected;
    std::vector<std::string> options {"Start Game", "Rules", "Exit"};
public:
    void load() override;
    std::string getInput();
};
