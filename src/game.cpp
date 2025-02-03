#include "game.hpp"
#include "scenes/scene.cpp"

Game::Game()
{
    srand(time(NULL));
    getmaxyx(stdscr, yMax, xMax);
    isInit = true;
}

void Game::setupGame()
{
    gameScene = new GameScene();
    gameScene->load();
}

void Game::rules()
{
    // code
}

void Game::run()
{
    if (!isInit)
        return;

    mainMenuScene = new MainMenuScene();
    mainMenuScene->load();
    std::string input = mainMenuScene->getInput();
    
    if (input == "Start Game")
       setupGame();
    else if (input == "Rules")
       rules();
    else if (input == "Exit")
       endwin();
}
