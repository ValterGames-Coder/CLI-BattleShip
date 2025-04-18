#include "game.hpp"

Game::Game()
{
    srand(time(NULL));
    getmaxyx(stdscr, m_yMax, m_xMax);
    m_gameType = Null;
    m_state = Start;
    m_isInit = true;
}

void Game::updateDialog(Board* board, Dialog* dialog, int multiply)
{
    unsigned numberOfShips = board->ships.size();
    std::wstring text = L"Ships: ";
    text += std::to_wstring(numberOfShips);
    if (dialog == nullptr)
    {
        dialog = new Dialog(Position(
            (m_yMax / 2) + BOARD_SPACE_Y * 1.5,
            (m_xMax / 2) + BOARD_SPACE_X * multiply
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
    for (auto size : m_playerShips)
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
    for (auto size : m_enemyShips)
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
    unsigned enemyNumberOfShips = m_gameScene->enemyBoard->ships.size();
    if (enemyNumberOfShips == 0)
    {
        if (m_gameType == PlayerVSBot)
        {
            m_state = Win;
            m_gameScene->endMenu("./img/win.txt", COLOR_YELLOW);
            return;
        }
        else
        {
            m_state = Win;
            m_gameScene->endMenu("./img/player1win.txt", COLOR_YELLOW);
            return;
        }
    }
    unsigned playerNumberOfShips = m_gameScene->playerBoard->ships.size();
    if (playerNumberOfShips == 0)
    {
        if (m_gameType == PlayerVSBot)
        {
            m_state = Lose;
            m_gameScene->endMenu("./img/lose.txt", COLOR_RED);
            return;
        }
        else
        {
            m_state = Win;
            m_gameScene->endMenu("./img/player2win.txt", COLOR_YELLOW);
            return;
        }
    }
}

void Game::updateCursor(Cursor* cursor, Board* board)
{
    cursor->setBoard(board);
    board->drawCell(cursor->position, Cell(Aim), UI);
    board->update();
}

void Game::gameLoop(Cursor* cursor, Board* playerBoard, Board* enemyBoard, Bot* bot)
{
    m_state = Play;
    unsigned steps = 0;
    Board* currentBoard;
    Position enemyCursorPosition, playerCursorPosition;
    cursor->move({ 0, 0 });
    do
    {
        checkGameState();
        if (m_state != Play)
            break;
        updateDialog(m_gameScene->playerBoard, m_gameScene->playerShipsDialog, -1);
        updateDialog(m_gameScene->enemyBoard, m_gameScene->enemyShipsDialog, 1);
        currentBoard = steps % 2 == 0 ? enemyBoard : playerBoard;
        wchar_t input;
        updateCursor(cursor, currentBoard);
        input = cursor->readKeyboard();
        cursor->checkCollision({ 1, 1 });
        if (input == 10) {
            bool canShoot = currentBoard->canShoot(cursor->position);
            if (!canShoot)
                continue;
            CellType type = shoot(cursor->position, currentBoard);
            if (type == Hit)
                continue;
            if (m_gameType == PlayerVSBot)
                bot->makeStep();
            else
                steps++;
            cursor->move(steps % 2 == 0 ? enemyCursorPosition : playerCursorPosition);
        }
        if (steps % 2 == 0)
            enemyCursorPosition = cursor->position;
        else
            playerCursorPosition = cursor->position;
    } while (1);
    getch();
    run();
}

void Game::startGame()
{
    m_gameScene = new GameScene();
    Board* enemyBoard = m_gameScene->enemyBoard;
    Board* playerBoard = m_gameScene->playerBoard;
    Cursor* cursor = new Cursor(playerBoard);
    if (m_gameType == PlayerVSBot)
    {
        Bot* bot = new Bot(playerBoard);
        enemyBoard->shipsVisible = false;
        setupPlayerShips(cursor, playerBoard);
        setupEnemyShips(enemyBoard);
        gameLoop(cursor, playerBoard, enemyBoard, bot);
    }
    else if (m_gameType == PlayerVSPlayer)
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
    m_rulesScene = new RulesScene();
    run();
}

void Game::run()
{
    if (!m_isInit)
        throw "Game isn't init!";

    m_mainMenuScene = new MainMenuScene();
    std::string input = m_mainMenuScene->getInput();

    if (input == "Player vs Player")
    {
        m_gameType = PlayerVSPlayer;
        startGame();
    }
    else if (input == "Player vs Bot")
    {
        m_gameType = PlayerVSBot;
        startGame();
    }
    else if (input == "Rules")
        rules();
    else if (input == "Exit")
        endwin();
}