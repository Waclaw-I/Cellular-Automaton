#include "Cell.h"

unsigned Cell::amount = 0;

Cell::Cell() : 
	id(++amount), alive(false), group(0) {}
