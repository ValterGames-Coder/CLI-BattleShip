#include "game.hpp"
#include "scenes/scene.cpp"
#include "logic/cursor.hpp"
#include "logic/ship_builder.hpp"
#include "logic/shooter.hpp"

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
                if (addShip(gameScene->playerBoard, ship, cursor->cursorPosition))
                    break;
            cursor->checkCollision(ship->getSize());
            ship->draw(cursor->cursorPosition);
        } while (1);
    }
}

void Game::setupEnemyShips(Board* enemyBoard)
{
    for(auto size : enemyShips)
    {
        Ship* ship = new Ship(size, enemyBoard);
        bool canShipAdd;
        do
        {
            bool rotate = (rand() % 4) == 0;
            if (rotate)
                ship->rotate();
            Position maxPosition(BOARD_SIZE - ship->getSize().first, BOARD_SIZE - ship->getSize().second);
            Position shipPosition(rand() % maxPosition.y, rand() % maxPosition.x);
            canShipAdd = addShip(enemyBoard, ship, shipPosition);
        } while (!canShipAdd);
    }
}

void Game::gameLoop(Cursor* cursor, Board* enemyBoard)
{
    do
    {
        wchar_t input;
        input = cursor->readKeyboard();
        cursor->checkCollision({1, 1});
        enemyBoard->drawCell(cursor->cursorPosition, Cell(Aim), UI);
        enemyBoard->update();
        if (input == 10) {
            bool canShoot = enemyBoard->canShoot(cursor->cursorPosition);
            if(!canShoot)
                continue;
            shoot(cursor->cursorPosition, enemyBoard);
            //bot->make_step();
            //cursor->move(cursor->position);
        }
    } while (1);
}

void Game::startGame()
{
    gameScene = new GameScene();
    gameScene->load();
    Board* enemyBoard = gameScene->enemyBoard;
    Cursor* cursor = new Cursor(gameScene->playerBoard);
    //enemyBoard->shipsVisable = false;
    setupPlayerShips(cursor);
    setupEnemyShips(enemyBoard);
    gameScene->dialog->updateDialog(L"for move: ← → ↑ ↓ | for shoot: enter");
    cursor->move({0, 0});
    enemyBoard->drawCell(cursor->cursorPosition, Cell(Aim), UI);
    enemyBoard->update();
    gameLoop(cursor, enemyBoard);
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
        startGame();
    else if (input == "Rules")
        rules();
    else if (input == "Exit")
        endwin();
}
