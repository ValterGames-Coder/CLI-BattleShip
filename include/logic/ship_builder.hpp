#pragma once
#include "logic/ship.hpp"
#include "logic/board.hpp"
#include "base/position.hpp"
#include <algorithm>

bool addShip(Board* board, Ship* ship, Position shipPosition);
void deleteShip(Board* board, Position position);
