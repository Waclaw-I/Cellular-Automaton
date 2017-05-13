#pragma once

#include "Displayer.h"

class CellPopulator
{
public:
	static unsigned ACTUAL_GROUP;

	void addCellByClick(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window);

private:
	
};