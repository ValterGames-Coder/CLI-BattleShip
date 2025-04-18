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
    static bool m_intro;
    unsigned m_selected;
    std::vector<std::string> m_options {"Player vs Player", "Player vs Bot", "Rules", "Exit"};
public:
    MainMenuScene();
    void load() override;
    std::string getInput();
};
