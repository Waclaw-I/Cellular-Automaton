#include "Cell.h"
#include "Resources.h"
#include <iostream>

unsigned Cell::amount = 0;

Cell::Cell() : 
	id(++amount),
	alive(false),
	in_range(false),
	group(0),
	crystalized(false),
	my_ro(0),
	energy(0) {}


bool Cell::isRoExceeded()
{
	if (my_ro > static_cast<double>(4215840142323.42 / CELL_AMOUNT))
	{
		return true;
	}

	return false;
}

