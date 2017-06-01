#include "Resources.h"

  unsigned CELL_WIDTH_AMOUNT = 100;
  unsigned CELL_HEIGHT_AMOUNT = 100;
  unsigned CELL_AMOUNT = CELL_WIDTH_AMOUNT * CELL_HEIGHT_AMOUNT;
  unsigned MAP_WIDTH = 500;
  unsigned MAP_HEIGHT = 500;
  unsigned WINDOW_WIDTH = 1000;
  unsigned WINDOW_HEIGHT = 500;
  unsigned CELL_WIDTH = MAP_WIDTH / CELL_WIDTH_AMOUNT;
  unsigned CELL_HEIGHT = MAP_HEIGHT / CELL_HEIGHT_AMOUNT;
  unsigned MAX_GROUPS = 30;
  unsigned RANGE = 5;
  unsigned RANDOM_R_TRIES = 3000;
  unsigned DISPLAY_WIDTH = 1000;
  unsigned DISPLAY_HEIGHT = 1000;
  unsigned DISPLAY_CELL_WIDTH = DISPLAY_WIDTH / CELL_WIDTH_AMOUNT;
  unsigned DISPLAY_CELL_HEIGHT = DISPLAY_HEIGHT / CELL_HEIGHT_AMOUNT;
  double A = 86710969050178.5;
  double B = 9.41268203527779;
  double e = 2.71828182845904523536;
  double game_speed = 5;
  unsigned k = 100; // for crystalization
  double Ro = 1;
  double previous_Ro = 0;
  double leftover_Ro = 0;   double monte_carlo_groups = 15;