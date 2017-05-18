#pragma once

class Cell
{
public:
	unsigned id;
	unsigned group;
	bool alive;
	bool in_range;

	Cell();

private:
	static unsigned amount;
};