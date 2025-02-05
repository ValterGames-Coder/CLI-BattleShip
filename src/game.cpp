#include "game.hpp"
#include "scenes/scene.cpp"
#include "logic/cursor.hpp"

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
    Ship* ship = new Ship(4, gameScene->playerBoard);
    ship->draw({0, 0});
    Cursor* cursor = new Cursor(gameScene->playerBoard);
    //cursor->cursorPosition = ship->getSize();
    wchar_t input;
    do
    {
        input = cursor->readKeyboard();
        ship->draw(cursor->cursorPosition);
    } while (input != 10);
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
