#pragma once

#include "Displayer.h"

class CellPopulator
{
public:
	static unsigned ACTUAL_GROUP;

	void addCellByClick(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, bool allowSwipe);
	void addCellByRandom(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, int amount);
	void addCellEqually(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, int amount);
	void addCellRandom_R(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, int range, GameConditions& game_conditions);
	void randomizeMap(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, int amount);

private:
	void markCellsInRange(Map& map, std::pair<int, int> cell_index, std::pair<int,int> up_left, std::pair<int, int> down_right, int range);
	
};