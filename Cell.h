#pragma once

class Cell
{
public:
	unsigned id;
	unsigned group;
	double my_ro;
	bool alive;
	bool in_range;
	bool crystalized;

	Cell();

	bool isRoExceeded();

private:
	static unsigned amount;
};