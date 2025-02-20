#include <algorithm>
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

void Game::updateDialogs()
{
    unsigned short playerNumberOfShips = std::count_if(
        gameScene->playerBoard->ships.begin(), 
        gameScene->playerBoard->ships.end(),
        [&](Ship* ship) { return ship->isDestroyed == false; });
    unsigned short enemyNumberOfShips = std::count_if(
        gameScene->enemyBoard->ships.begin(), 
        gameScene->enemyBoard->ships.end(),
        [&](Ship* ship) { return ship->isDestroyed == false; });
    wchar_t enemyShipsDialogText[20];
    wchar_t playerShipsDialogText[20];
    std::swprintf(playerShipsDialogText, sizeof(playerShipsDialogText) / sizeof(wchar_t), L"Корабли: %i", playerNumberOfShips);
    std::swprintf(enemyShipsDialogText, sizeof(enemyShipsDialogText) / sizeof(wchar_t), L"Корабли: %i", enemyNumberOfShips);
    if (gameScene->playerShipsDialog == nullptr)
    {
        gameScene->playerShipsDialog = new Dialog(Position(
            (yMax / 2) + BOARD_SPACE_Y * 1.5,
            (xMax / 2) - BOARD_SPACE_X
        ), playerShipsDialogText, true, 18);
        gameScene->enemyShipsDialog = new Dialog(Position(
            (yMax / 2) + BOARD_SPACE_Y * 1.5,
            (xMax / 2) + BOARD_SPACE_X
        ), enemyShipsDialogText, true, 18);
    }
    else
    {
        gameScene->playerShipsDialog->updateDialog(playerShipsDialogText);
        gameScene->enemyShipsDialog->updateDialog(enemyShipsDialogText);
    }
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
                if (addShip(gameScene->playerBoard, ship, cursor->position))
                    break;
            cursor->checkCollision(ship->getSize());
            ship->draw(cursor->position);
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

void Game::checkState()
{
    unsigned short enemyNumberOfShips = std::count_if(
        gameScene->enemyBoard->ships.begin(), 
        gameScene->enemyBoard->ships.end(),
        [&](Ship* ship) { return ship->isDestroyed == false; });
    if (enemyNumberOfShips == 0)
    {
        state = Win;
        gameScene->win();
        return;
    }
    unsigned short playerNumberOfShips = std::count_if(
        gameScene->playerBoard->ships.begin(), 
        gameScene->playerBoard->ships.end(),
        [&](Ship* ship) { return ship->isDestroyed == false; });
    if (playerNumberOfShips == 0)
    {
        state = Lose;
        gameScene->lose();
        return;
    }
}

void Game::gameLoop(Cursor* cursor, Board* enemyBoard, Bot* bot)
{
    setupPlayerShips(cursor);
    setupEnemyShips(enemyBoard);
    state = Play;
    cursor->move({0, 0});
    enemyBoard->drawCell(cursor->position, Cell(Aim), UI);
    enemyBoard->update();
    do
    {
        checkState();
        if (state != Play)
            break;
        updateDialogs();
        wchar_t input;
        input = cursor->readKeyboard();
        cursor->checkCollision({1, 1});
        enemyBoard->drawCell(cursor->position, Cell(Aim), UI);
        enemyBoard->update();
        if (input == 10) {
            bool canShoot = enemyBoard->canShoot(cursor->position);
            if(!canShoot)
                continue;
            CellType type = shoot(cursor->position, enemyBoard);
            if (type == Hit)
                continue;
            bot->makeStep();
            cursor->move(cursor->position);
        }
    } while (1);
    getch();
    run();
}

void Game::startGame()
{
    gameScene = new GameScene();
    gameScene->load();
    Board* enemyBoard = gameScene->enemyBoard;
    Cursor* cursor = new Cursor(gameScene->playerBoard);
    Bot* bot = new Bot(gameScene->playerBoard);
    enemyBoard->shipsVisable = false;
    gameLoop(cursor, enemyBoard, bot);
}
    

void Game::rules()
{
    rulesScene = new RulesScene();
    rulesScene->load();
    run();
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
