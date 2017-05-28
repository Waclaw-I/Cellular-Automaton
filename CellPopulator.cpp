#include "CellPopulator.h"
#include "Resources.h"

unsigned CellPopulator::ACTUAL_GROUP = 0;

void CellPopulator::addCellByClick(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, bool allowSwipe)
{
	for (int i = 0; i < map.size(); ++i)
	{
		auto&& col_size = map[i].size();
		for (int j = 0; j < col_size; ++j)
		{
			if (displayer.lookForInput(i, j, window, allowSwipe))
			{
				map[i][j].alive = true;
				map[i][j].group = ACTUAL_GROUP++;
				displayer.updateGraphicCell(i, j, map[i][j].group, window);
				if (ACTUAL_GROUP == MAX_GROUPS) ACTUAL_GROUP = 0;
			}
		}
	}
}

void CellPopulator::addCellByRandom(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, int amount)
{
	for (int k = 0; k < amount; ++k)
	{
		int i = rand() % map.size();
		int j = rand() % map[0].size();

		map[i][j].alive = true;
		map[i][j].group = ACTUAL_GROUP++;
		displayer.updateGraphicCell(i, j, map[i][j].group, window);
		if (ACTUAL_GROUP == MAX_GROUPS) ACTUAL_GROUP = 0;
	}
}

void CellPopulator::randomizeMap(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, int amount)
{
	for (int i = 0; i < map.size(); ++i)
	{
		auto&& col_size = map[i].size();
		for (int j = 0; j < col_size; ++j)
		{
			map[i][j].alive = true;
			map[i][j].group = rand() % amount;
			displayer.updateGraphicCell(i, j, map[i][j].group, window);
		}
	}
}

void CellPopulator::addCellEqually(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, int amount)
{
	int step = (CELL_HEIGHT_AMOUNT * CELL_WIDTH_AMOUNT) / amount;
	int it = step;
	for (int k = 0; k < amount; ++k)
	{
		int i = it / CELL_WIDTH_AMOUNT;
		int j = it % CELL_WIDTH_AMOUNT;
		map[i][j].alive = true;
		map[i][j].group = ACTUAL_GROUP++;
		displayer.updateGraphicCell(i, j, map[i][j].group, window);
		if (ACTUAL_GROUP == MAX_GROUPS) ACTUAL_GROUP = 0;
		it += step;
	}
}

void CellPopulator::markCellsInRange(Map& map, std::pair<int, int> cell_index, std::pair<int, int> up_left, std::pair<int, int> down_right, int range)
{
	auto distance = [](std::pair<int, int> p, std::pair<int, int> q)->double {
		return std::sqrt(std::pow(q.first - p.first, 2) + std::pow(q.second - p.second, 2));
	};

	for (int i = up_left.first; i <= down_right.first; ++i)
	{
		for (int j = up_left.second; j <= down_right.second; ++j)
		{
			if (cell_index.first == i && cell_index.second == j || map[i][j].in_range) continue;
			double dist = distance(cell_index, { i, j });
			if ( dist <= range) map[i][j].in_range = true;
			else map[i][j].in_range = false;
		}
	}
}

void CellPopulator::addCellRandom_R(Map& map, Displayer& displayer, std::unique_ptr<sf::RenderWindow>& window, int range, GameConditions& game_conditions)
{
	for (int k = 0; k < RANDOM_R_TRIES; ++k)
	{
		int i = rand() % map.size();
		int j = rand() % map[0].size();
		auto& cell = map[i][j];
		auto&& size = map.size();

		if (cell.alive == false && cell.in_range == false)
		{
			cell.alive = true;
			cell.group = ACTUAL_GROUP++;
			displayer.updateGraphicCell(i, j, cell.group, window);
			if (ACTUAL_GROUP == MAX_GROUPS) ACTUAL_GROUP = 0;
			std::pair<int, int> up_left = { i - range, j - range };
			std::pair<int, int>down_right = { i + range, j + range };

			up_left.first = std::max(i - range, 0);
			up_left.second = std::max(j - range, 0);
			down_right.first = std::min(i + range, static_cast<int>(size-1));
			down_right.second = std::min(j + range, static_cast<int>(size-1));

				
			markCellsInRange(map, { i, j }, up_left, down_right, range);

		}
	}
}


