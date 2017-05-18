#pragma once
#include <vector>
#include <array>
#include "Cell.h"


using Map = std::vector<std::vector<Cell>>;

//unsigned MENU_WINDOW_WIDTH = 600;
//unsigned MENU_WINDOW_HEIGHT = 400;

constexpr unsigned CELL_WIDTH_AMOUNT = 50;
constexpr unsigned CELL_HEIGHT_AMOUNT = 50;
constexpr unsigned MAP_WIDTH = 500;
constexpr unsigned MAP_HEIGHT = 500;
constexpr unsigned WINDOW_WIDTH = 1000;
constexpr unsigned WINDOW_HEIGHT = 500;
constexpr unsigned CELL_WIDTH = MAP_WIDTH / CELL_WIDTH_AMOUNT;
constexpr unsigned CELL_HEIGHT = MAP_HEIGHT / CELL_HEIGHT_AMOUNT;
constexpr unsigned MAX_GROUPS = 30;
constexpr unsigned RANGE = 5;
constexpr unsigned RANDOM_R_TRIES = 3000;

using MyColor = std::array<unsigned char, 3>;


