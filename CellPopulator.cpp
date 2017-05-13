#include "CellPopulator.h"
#include "Resources.h"

unsigned CellPopulator::ACTUAL_GROUP = 0;

void CellPopulator::addCellByClick(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window)
{
	for (int i = 0; i < map.size(); ++i)
	{
		auto&& col_size = map[i].size();
		for (int j = 0; j < col_size; ++j)
		{
			if (displayer.lookForInput(i, j, window))
			{
				map[i][j].alive = true;
				map[i][j].group = ACTUAL_GROUP++;
				if (ACTUAL_GROUP == MAX_GROUPS) ACTUAL_GROUP = 0;
			}
		}
	}
}


