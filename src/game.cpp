#include "game.hpp"
#include "scenes/scene.cpp"
#include "logic/cursor.hpp"

Game::Game()
{
    srand(time(NULL));
    getmaxyx(stdscr, yMax, xMax);
    isInit = true;
}

void Game::setupPlayerShips(Cursor* cursor)
{
    wchar_t input;
    for(auto size : playerShips)
    {
        Ship* ship = new Ship(size, gameScene->playerBoard);
        cursor->move({0, 0});
        do
        {
            input = cursor->readKeyboard();
            if (input == 'r')
                ship->rotate();
            else if (input == 10)
            {
                bool addShip = gameScene->playerBoard->addShip(ship, cursor->cursorPosition);
                if (addShip)
                    break;
            }
            cursor->checkCollision(ship->getSize());
            ship->draw(cursor->cursorPosition);
        } while (1);
    }
}

void Game::setupGame()
{
    gameScene = new GameScene();
    gameScene->load();
    Cursor* cursor = new Cursor(gameScene->playerBoard);
    setupPlayerShips(cursor);
    getch();
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
