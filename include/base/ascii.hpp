#pragma once
#include <vector>
#include <fstream>
#include <ncurses.h>
#include <string>
#include "base/position.hpp"

void printImage(WINDOW* win, Position position, const char* fileName, unsigned short color);
Position getSize(const char* fileName);