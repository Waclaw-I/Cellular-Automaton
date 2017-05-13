#pragma once
#include <vector>
#include <array>
#include "Cell.h"


using Map = std::vector<std::vector<Cell>>;

//unsigned MENU_WINDOW_WIDTH = 600;
//unsigned MENU_WINDOW_HEIGHT = 400;

constexpr unsigned MAP_WIDTH = 60;
constexpr unsigned MAP_HEIGHT = 60;
constexpr unsigned WINDOW_WIDTH = 500;
constexpr unsigned WINDOW_HEIGHT = 500;
constexpr unsigned CELL_WIDTH = WINDOW_WIDTH / MAP_WIDTH;
constexpr unsigned CELL_HEIGHT = WINDOW_HEIGHT / MAP_HEIGHT;
constexpr unsigned MAX_GROUPS = 30;

using MyColor = std::array<unsigned char, 3>;


