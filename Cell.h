#pragma once

class Cell
{
public:
	unsigned id;
	unsigned group;
	bool alive;

	Cell();

private:
	static unsigned amount;
};