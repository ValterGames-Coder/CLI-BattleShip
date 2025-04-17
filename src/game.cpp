#include "game.hpp"

Game::Game()
{
    srand(time(NULL));
    getmaxyx(stdscr, yMax, xMax);
    isInit = true;
}

void Game::updateDialog(Board* board, Dialog* dialog, short multiply)
{
    unsigned short numberOfShips = board->ships.size();
    std::wstring text = L"Ships: ";
    text += std::to_wstring(numberOfShips);
    if (dialog == nullptr)
    {
        dialog = new Dialog(Position(
            (yMax / 2) + BOARD_SPACE_Y * 1.5,
            (xMax / 2) + BOARD_SPACE_X * multiply
        ), text, true, 18);
    }
    else
    {
        dialog->updateDialog(text);
    }
}

void Game::setupPlayerShips(Cursor* cursor, Board* board)
{
    wchar_t input;
    for (auto size : playerShips)
    {
        Ship* ship = new Ship(size, board);
        cursor->move({ 0, 0 });
        do
        {
            input = cursor->readKeyboard();
            if (input == 'r')
                ship->rotate();
            else if (input == 10)
                if (addShip(board, ship, cursor->position))
                    break;
            cursor->checkCollision(ship->getSize());
            ship->draw(cursor->position);
        } while (1);
    }
}

void Game::setupEnemyShips(Board* enemyBoard)
{
    for (auto size : enemyShips)
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

void Game::checkGameState()
{
    unsigned short enemyNumberOfShips = 
        gameScene->enemyBoard->ships.size();
    if (enemyNumberOfShips == 0)
    {
        if (gameType == PlayerVSBot)
        {
            state = Win;
            gameScene->endMenu("./img/win.txt", COLOR_YELLOW);
            return;
        }
        else
        {
            state = Win;
            gameScene->endMenu("./img/player1win.txt", COLOR_YELLOW);
            return;
        }
    }
    unsigned short playerNumberOfShips =
        gameScene->playerBoard->ships.size();
    if (playerNumberOfShips == 0)
    {
        if (gameType == PlayerVSBot)
        {
            state = Lose;
            gameScene->endMenu("./img/lose.txt", COLOR_RED);
            return;
        }
        else
        {
            state = Win;
            gameScene->endMenu("./img/player2win.txt", COLOR_YELLOW);
            return;
        }
    }
}

void Game::gameLoop(Cursor* cursor, Board* playerBoard, Board* enemyBoard, Bot* bot)
{
    state = Play;
    cursor->move({ 0, 0 });
    enemyBoard->drawCell(cursor->position, Cell(Aim), UI);
    enemyBoard->update();
    int steps = 0;
    Board* currentBoard;
    do
    {
        checkGameState();
        if (state != Play)
            break;
        updateDialog(gameScene->playerBoard, gameScene->playerShipsDialog, -1);
        updateDialog(gameScene->enemyBoard, gameScene->enemyShipsDialog, 1);
        currentBoard = steps % 2 == 0 ? enemyBoard : playerBoard;
        wchar_t input;
        cursor->setBoard(currentBoard);
        input = cursor->readKeyboard();
        cursor->checkCollision({ 1, 1 });
        currentBoard->drawCell(cursor->position, Cell(Aim), UI);
        currentBoard->update();
        if (input == 10) {
            bool canShoot = currentBoard->canShoot(cursor->position);
            if (!canShoot)
                continue;
            CellType type = shoot(cursor->position, currentBoard);
            if (type == Hit)
                continue;
            if (gameType == PlayerVSBot)
            {
                bot->makeStep();
                cursor->move(cursor->position);
            }
            else
            {
                steps++;
            }
        }
    } while (1);
    getch();
    run();
}

void Game::startGame()
{
    gameScene = new GameScene();
    Board* enemyBoard = gameScene->enemyBoard;
    Board* playerBoard = gameScene->playerBoard;
    Cursor* cursor = new Cursor(playerBoard);
    if (gameType == PlayerVSBot)
    {
        Bot* bot = new Bot(playerBoard);
        enemyBoard->shipsVisible = false;
        setupPlayerShips(cursor, playerBoard);
        setupEnemyShips(enemyBoard);
        gameLoop(cursor, playerBoard, enemyBoard, bot);
    }
    else if (gameType == PlayerVSPlayer)
    {
        setupPlayerShips(cursor, playerBoard);
        playerBoard->shipsVisible = false;
        playerBoard->update();
        setupPlayerShips(cursor, enemyBoard);
        enemyBoard->shipsVisible = false;
        playerBoard->update();
        gameLoop(cursor, playerBoard, enemyBoard);
    }
}


void Game::rules()
{
    rulesScene = new RulesScene();
    run();
}

void Game::run()
{
    if (!isInit)
        return;

    mainMenuScene = new MainMenuScene();
    std::string input = mainMenuScene->getInput();

    if (input == "Player vs Player")
    {
        gameType = PlayerVSPlayer;
        startGame();
    }
    else if (input == "Player vs Bot")
    {
        gameType = PlayerVSBot;
        startGame();
    }
    else if (input == "Rules")
        rules();
    else if (input == "Exit")
        endwin();
}