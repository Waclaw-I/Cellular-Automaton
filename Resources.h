#pragma once
#include <vector>
#include <array>
#include "Cell.h"

using Map = std::vector<std::vector<Cell>>;
using MyColor = std::array<unsigned char, 3>;

extern  unsigned CELL_WIDTH_AMOUNT;
extern  unsigned CELL_HEIGHT_AMOUNT;
extern  unsigned CELL_AMOUNT;
extern  unsigned MAP_WIDTH;
extern  unsigned MAP_HEIGHT;
extern  unsigned WINDOW_WIDTH;
extern  unsigned WINDOW_HEIGHT;
extern  unsigned CELL_WIDTH;
extern  unsigned CELL_HEIGHT;
extern  unsigned MAX_GROUPS;
extern  unsigned RANGE;
extern  unsigned RANDOM_R_TRIES;
extern  unsigned DISPLAY_WIDTH;
extern  unsigned DISPLAY_HEIGHT;
extern  unsigned DISPLAY_CELL_WIDTH;
extern  unsigned DISPLAY_CELL_HEIGHT;
extern  double A;
extern  double B;
extern  double e;
extern  double game_speed;
extern  unsigned k;
extern  double Ro;
extern  double previous_Ro;
extern  double leftover_Ro;
extern  double monte_carlo_groups;




