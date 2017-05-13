#include "MapGenerator.h"


Map MapGenerator::createNewMap(int width, int height)
{
	Map map(height);
	for (auto& row : map)
	{
		row = std::vector<Cell>(width);
	}

	return map;
}
