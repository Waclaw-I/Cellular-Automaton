#pragma once
#include <vector>
#include <array>
#include "Cell.h"


using Map = std::vector<std::vector<Cell>>;

//unsigned MENU_WINDOW_WIDTH = 600;
//unsigned MENU_WINDOW_HEIGHT = 400;

constexpr unsigned CELL_WIDTH_AMOUNT = 200;
constexpr unsigned CELL_HEIGHT_AMOUNT = 200;
constexpr unsigned CELL_AMOUNT = CELL_WIDTH_AMOUNT * CELL_HEIGHT_AMOUNT;
constexpr unsigned MAP_WIDTH = 500;
constexpr unsigned MAP_HEIGHT = 500;
constexpr unsigned WINDOW_WIDTH = 1000;
constexpr unsigned WINDOW_HEIGHT = 500;
constexpr unsigned CELL_WIDTH = MAP_WIDTH / CELL_WIDTH_AMOUNT;
constexpr unsigned CELL_HEIGHT = MAP_HEIGHT / CELL_HEIGHT_AMOUNT;
constexpr unsigned MAX_GROUPS = 30;
constexpr unsigned RANGE = 5;
constexpr unsigned RANDOM_R_TRIES = 3000;

constexpr unsigned DISPLAY_WIDTH = 1000;
constexpr unsigned DISPLAY_HEIGHT = 1000;

constexpr unsigned DISPLAY_CELL_WIDTH = DISPLAY_WIDTH / CELL_WIDTH_AMOUNT;
constexpr unsigned DISPLAY_CELL_HEIGHT = DISPLAY_HEIGHT / CELL_HEIGHT_AMOUNT;




constexpr double A = 86710969050178.5;
constexpr double B = 9.41268203527779;

constexpr double e = 2.71828182845904523536;

static double game_speed = 5;

constexpr unsigned k = 100; // for crystalization
static double Ro = 1;
static double previous_Ro = 0;
static double leftover_Ro = 0;

static double monte_carlo_groups = 15;



using MyColor = std::array<unsigned char, 3>;


