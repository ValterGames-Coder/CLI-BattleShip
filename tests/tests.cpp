#include "libs/catch_amalgamated.hpp"
#include "logic/ship_builder.hpp"

// TEST_CASE("Успешное добавление корабля в допустимую позицию", "[addShip]")
// {
//     Board* board = new Board(Position(0, 0));
//     REQUIRE(addShip(board, new Ship(4, board), Position(0, 0)));
//     REQUIRE(board->ships.size() == 1);
// }

// TEST_CASE("Попытка добавить корабль за пределы доски", "[addShip]")
// {
//     Board* board = new Board(Position(0, 0));
//     REQUIRE(addShip(board, new Ship(4, board), Position(11, 11)) == false);
//     REQUIRE(board->ships.size() == 0);
// }

// TEST_CASE("Успешное удаление существующего корабля", "[addShip, deleteShip]")
// {
//     Board* board = new Board(Position(0, 0));
//     Position shipPosition(0, 0);
//     addShip(board, new Ship(4, board), shipPosition);
//     deleteShip(board, shipPosition);
//     REQUIRE(board->getCells(Undamaged).size() == 0);
//     REQUIRE(board->getCells(Locked).size() == 0);
// }

TEST_CASE("Попытка удалить несуществующий корабль", "[addShip, deleteShip]")
{
    Board* board = new Board(Position(0, 0));
    Position shipPosition(0, 0);
    deleteShip(board, shipPosition);
    REQUIRE(board->getCells(Undamaged).size() == 0);
    REQUIRE(board->getCells(Locked).size() == 0);
}