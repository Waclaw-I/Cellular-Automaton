#include "Engine.h"
#include <Windows.h>
#include "GameConditions.h"


void Engine::Wait()
{
	Sleep(1000 / GameData::game_speed); // windows only 
}


unsigned Engine::getNeighboursAmount(unsigned w, unsigned h, Map& map, Neighbours neighbours)
{
	unsigned neighbours_amount = 0;

	for (auto& cell : neighbours)
	{
		if (map[cell.second][cell.first].alive)
			neighbours_amount++;
	}
	return neighbours_amount;
}

Map Engine::designateNextFrame(Map& map, NeighbourType neighbourhood, BoundaryCondition boundary_cond) // for GameOfLife
{
	Map new_map(map);
	for (int i = 0; i < CELL_HEIGHT_AMOUNT; ++i)
	{
		for (int j = 0; j < CELL_WIDTH_AMOUNT; ++j)
		{
			auto& old_cell = map[i][j];
			auto& new_cell = new_map[i][j];
			auto& neighbours = getNeighbours(j, i, map, neighbourhood, boundary_cond);
			unsigned neighbours_amount = getNeighboursAmount(j, i, map, neighbours);
			if (neighbours_amount < 2 || neighbours_amount > 3)
			{
				if (old_cell.alive == true) new_cell.alive = false; // cell dies
				continue;
			}
			if (neighbours_amount == 3)
			{
				if (old_cell.alive == false) new_cell.alive = true; // cell is born
			}

		}
	}
	return new_map;
}

Map Engine::makeSeedsGrow(Map& map, NeighbourType& neighbour_type, BoundaryCondition& boundary_cond)
{
	Map new_map(map);
	for (int i = 0; i < CELL_HEIGHT_AMOUNT; ++i)
	{
		for (int j = 0; j < CELL_WIDTH_AMOUNT; ++j)
		{
			auto& old_cell = map[i][j];
			auto& neighbours = getNeighbours(j, i, map, neighbour_type, boundary_cond);
			{
				if (old_cell.alive == true) 
					for (auto& neighbour : neighbours)
					{
						if (map[neighbour.second][neighbour.first].alive)
							continue;
						else
						{
							new_map[neighbour.second][neighbour.first].alive = true;
							new_map[neighbour.second][neighbour.first].group = old_cell.group;
						}
					}
			}
		}
	}
	return new_map;
}





Engine::Neighbours Engine::PeriodicMoore(unsigned w, unsigned h, Map& map)
{
	Neighbours neighbours = { { w - 1, h - 1 },{ w, h - 1 },{ w + 1, h - 1 },
							  { w + 1, h },{ w + 1, h + 1 },{ w, h + 1 },
							  { w - 1, h + 1 },{ w - 1, h } };
	for (auto& cell : neighbours)
	{
		if (cell.first == CELL_WIDTH_AMOUNT) cell.first = 0;
		else if (cell.first == -1) cell.first = CELL_WIDTH_AMOUNT - 1;

		if (cell.second == CELL_HEIGHT_AMOUNT) cell.second = 0;
		else if (cell.second == -1) cell.second = CELL_HEIGHT_AMOUNT - 1;
	}

	return neighbours;


}
Engine::Neighbours Engine::PeriodicNeumann(unsigned w, unsigned h, Map& map)
{
	Neighbours all_neighbours = PeriodicMoore(w, h, map);
	Neighbours neighbours;
	neighbours.push_back(all_neighbours[1]);
	neighbours.push_back(all_neighbours[3]);
	neighbours.push_back(all_neighbours[5]);
	neighbours.push_back(all_neighbours[7]);

	return neighbours;
}
Engine::Neighbours Engine::PeriodicHexLeft(unsigned w, unsigned h, Map& map)
{
	Neighbours all_neighbours = PeriodicMoore(w, h, map);
	Neighbours neighbours;
	neighbours.push_back(all_neighbours[0]);
	neighbours.push_back(all_neighbours[1]);
	neighbours.push_back(all_neighbours[3]);
	neighbours.push_back(all_neighbours[4]);
	neighbours.push_back(all_neighbours[5]);
	neighbours.push_back(all_neighbours[7]);

	return neighbours;
}
Engine::Neighbours Engine::PeriodicHexRight(unsigned w, unsigned h, Map& map)
{
	Neighbours all_neighbours = PeriodicMoore(w, h, map);
	Neighbours neighbours;
	neighbours.push_back(all_neighbours[1]);
	neighbours.push_back(all_neighbours[2]);
	neighbours.push_back(all_neighbours[3]);
	neighbours.push_back(all_neighbours[5]);
	neighbours.push_back(all_neighbours[6]);
	neighbours.push_back(all_neighbours[7]);

	return neighbours;
}
Engine::Neighbours Engine::PeriodicHexRandom(unsigned w, unsigned h, Map& map)
{
	int random = rand() % 2;
	if (random) // check if working
		return PeriodicHexLeft(w, h, map);
	else
		return PeriodicHexRight(w, h, map);
}
Engine::Neighbours Engine::PeriodicPentaLeft(unsigned w, unsigned h, Map& map)
{
	Neighbours all_neighbours = PeriodicMoore(w, h, map);
	Neighbours neighbours;
	neighbours.push_back(all_neighbours[0]);
	neighbours.push_back(all_neighbours[1]);
	neighbours.push_back(all_neighbours[5]);
	neighbours.push_back(all_neighbours[6]);
	neighbours.push_back(all_neighbours[7]);

	return neighbours;
}
Engine::Neighbours Engine::PeriodicPentaRight(unsigned w, unsigned h, Map& map)
{
	Neighbours all_neighbours = PeriodicMoore(w, h, map);
	Neighbours neighbours;
	neighbours.push_back(all_neighbours[1]);
	neighbours.push_back(all_neighbours[2]);
	neighbours.push_back(all_neighbours[3]);
	neighbours.push_back(all_neighbours[4]);
	neighbours.push_back(all_neighbours[5]);

	return neighbours;
}
Engine::Neighbours Engine::PeriodicPentaUp(unsigned w, unsigned h, Map& map)
{
	Neighbours all_neighbours = PeriodicMoore(w, h, map);
	Neighbours neighbours;
	neighbours.push_back(all_neighbours[0]);
	neighbours.push_back(all_neighbours[1]);
	neighbours.push_back(all_neighbours[2]);
	neighbours.push_back(all_neighbours[3]);
	neighbours.push_back(all_neighbours[7]);

	return neighbours;
}
Engine::Neighbours Engine::PeriodicPentaDown(unsigned w, unsigned h, Map& map)
{
	Neighbours all_neighbours = PeriodicMoore(w, h, map);
	Neighbours neighbours;
	neighbours.push_back(all_neighbours[3]);
	neighbours.push_back(all_neighbours[4]);
	neighbours.push_back(all_neighbours[5]);
	neighbours.push_back(all_neighbours[6]);
	neighbours.push_back(all_neighbours[7]);

	return neighbours;
}
Engine::Neighbours Engine::PeriodicPentaRandom(unsigned w, unsigned h, Map& map)
{
	int random = rand() % 4;
	if (random == 0)
		return PeriodicPentaLeft(w, h, map);
	if (random == 1)
		return PeriodicPentaRight(w, h, map);
	if (random == 2)
		return PeriodicPentaUp(w, h, map);
	if (random == 3)
		return PeriodicPentaDown(w, h, map);
}

Engine::Neighbours Engine::Moore(unsigned w, unsigned h, Map& map)
{
	if (w != 0 && (w + 1) != CELL_WIDTH_AMOUNT && h != 0 && (h + 1) != CELL_HEIGHT_AMOUNT) // all others
		return{ { w - 1, h - 1 },{ w, h - 1 },{ w + 1, h - 1 },
		{ w + 1, h },{ w + 1, h + 1 },{ w, h + 1 },
		{ w - 1, h + 1 },{ w - 1, h } };

	if (w == 0)
	{
		if (h == 0)				   return{ { w + 1, h },{ w + 1, h + 1 },{ w, h + 1 } }; // upper-left corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w + 1, h },{ w + 1, h - 1 },{ w, h - 1 } }; // down-left corner
		return{ { w, h - 1 },{ w, h + 1 },{ w + 1, h - 1 },{ w + 1, h },{ w + 1, h + 1 } }; // left side
	}

	if ((w + 1) == CELL_WIDTH_AMOUNT)
	{
		if (h == 0)				   return{ { w - 1, h },{ w - 1, h + 1 },{ w, h + 1 } }; // upper-right corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w, h - 1 },{ w - 1, h - 1 },{ w - 1, h } }; // down-right corner
		return{ { w, h - 1 },{ w, h + 1 },{ w - 1, h - 1 },{ w - 1, h },{ w - 1, h + 1 } }; // right side
	}
	else
	{
		if (h == 0) return{ { w - 1, h },{ w + 1, h },{ w - 1, h + 1 },{ w, h + 1 },{ w + 1, h + 1 } }; // upper side
		if ((h + 1) == CELL_HEIGHT_AMOUNT)
			return{ { w - 1, h },{ w + 1, h },{ w - 1, h - 1 },{ w, h - 1 },{ w + 1, h - 1 } }; // down side
	}
}
Engine::Neighbours Engine::Neumann(unsigned w, unsigned h, Map& map)
{
	if (w != 0 && (w + 1) != CELL_WIDTH_AMOUNT && h != 0 && (h + 1) != CELL_HEIGHT_AMOUNT) // all others
		return{ { w, h - 1 }, { w + 1, h }, { w, h + 1 }, { w - 1, h } };

	if (w == 0)
	{
		if (h == 0)				   return{ { w + 1, h },{ w, h + 1 } }; // upper-left corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w + 1, h },{ w, h - 1 } }; // down-left corner
		return{ { w, h - 1 },{ w, h + 1 },{ w + 1, h } }; // left side
	}

	if ((w + 1) == CELL_WIDTH_AMOUNT)
	{
		if (h == 0)				   return{ { w - 1, h },{ w, h + 1 } }; // upper-right corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w, h - 1 },{ w - 1, h } }; // down-right corner
		return{ { w, h - 1 },{ w, h + 1 },{ w - 1, h } }; // right side
	}
	else
	{
		if (h == 0) return{ { w - 1, h },{ w + 1, h },{ w, h + 1 } }; // upper side
		if ((h + 1) == CELL_HEIGHT_AMOUNT)
			return{ { w - 1, h },{ w + 1, h },{ w, h - 1 } }; // down side
	}
}
Engine::Neighbours Engine::HexLeft(unsigned w, unsigned h, Map& map)
{
	if (w != 0 && (w + 1) != CELL_WIDTH_AMOUNT && h != 0 && (h + 1) != CELL_HEIGHT_AMOUNT) // all others
		return{ { w, h - 1 }, { w - 1, h - 1 }, { w + 1, h }, { w + 1, h + 1 }, { w , h + 1 },{ w - 1, h } };

	if (w == 0)
	{
		if (h == 0)				   return{ { w + 1, h },{ w + 1, h + 1 },{ w, h + 1 } }; // upper-left corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w + 1, h },{ w, h - 1 } }; // down-left corner
		return{ { w, h - 1 },{ w, h + 1 },{ w + 1, h },{ w + 1, h + 1 } }; // left side
	}

	if ((w + 1) == CELL_WIDTH_AMOUNT)
	{
		if (h == 0)				   return{ { w - 1, h },{ w, h + 1 } }; // upper-right corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w, h - 1 },{ w - 1, h - 1 },{ w - 1, h } }; // down-right corner
		return{ { w, h - 1 },{ w, h + 1 },{ w - 1, h - 1 },{ w - 1, h } }; // right side
	}
	else
	{
		if (h == 0) return{ { w - 1, h },{ w + 1, h },{ w, h + 1 },{ w + 1, h + 1 } }; // upper side
		if ((h + 1) == CELL_HEIGHT_AMOUNT)
			return{ { w - 1, h },{ w + 1, h },{ w - 1, h - 1 },{ w, h - 1 } }; // down side
	}
}
Engine::Neighbours Engine::HexRight(unsigned w, unsigned h, Map& map)
{
	if (w != 0 && (w + 1) != CELL_WIDTH_AMOUNT && h != 0 && (h + 1) != CELL_HEIGHT_AMOUNT) // all others
		return{{ w, h - 1 }, { w + 1, h - 1 }, { w + 1, h }, { w, h + 1 }, { w - 1, h + 1 }, { w - 1, h } };

	if (w == 0)
	{
		if (h == 0)				   return{ { w + 1, h }, { w, h + 1 } }; // upper-left corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w + 1, h },{ w + 1, h - 1 },{ w, h - 1 } }; // down-left corner
		return{ { w, h - 1 },{ w, h + 1 },{ w + 1, h - 1 },{ w + 1, h } }; // left side
	}

	if ((w + 1) == CELL_WIDTH_AMOUNT)
	{
		if (h == 0)				   return{ { w - 1, h },{ w - 1, h + 1 },{ w, h + 1 } }; // upper-right corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w, h - 1 },{ w - 1, h } }; // down-right corner
		return{ { w, h - 1 },{ w, h + 1 },{ w - 1, h },{ w - 1, h + 1 } }; // right side
	}
	else
	{
		if (h == 0) return{ { w - 1, h },{ w + 1, h },{ w - 1, h + 1 },{ w, h + 1 } }; // upper side
		if ((h + 1) == CELL_HEIGHT_AMOUNT)
			return{ { w - 1, h },{ w + 1, h },{ w, h - 1 },{ w + 1, h - 1 } }; // down side
	}
}
Engine::Neighbours Engine::HexRandom(unsigned w, unsigned h, Map& map)
{
	int random = rand() % 2;
	if (random) // check if working
		return HexLeft(w, h, map);
	else
		return HexRight(w, h, map);
}
Engine::Neighbours Engine::PentaLeft(unsigned w, unsigned h, Map& map)
{
	if (w != 0 && (w + 1) != CELL_WIDTH_AMOUNT && h != 0 && (h + 1) != CELL_HEIGHT_AMOUNT) // all others
		return{ { w - 1, h - 1 },{ w, h - 1 },{ w, h + 1 },{ w - 1, h + 1 },{ w - 1, h } };

	if (w == 0)
	{
		if (h == 0)				   return{ { w, h + 1 } }; // upper-left corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w, h - 1 } }; // down-left corner
		return{ { w, h - 1 },{ w, h + 1 } }; // left side
	}

	if ((w + 1) == CELL_WIDTH_AMOUNT)
	{
		if (h == 0)				   return{ { w - 1, h },{ w - 1, h + 1 },{ w, h + 1 } }; // upper-right corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w, h - 1 },{ w - 1, h - 1 },{ w - 1, h } }; // down-right corner
		return{ { w, h - 1 },{ w, h + 1 },{ w - 1, h - 1 },{ w - 1, h },{ w - 1, h + 1 } }; // right side
	}
	else
	{
		if (h == 0) return{ { w - 1, h },{ w - 1, h + 1 },{ w, h + 1 } }; // upper side
		if ((h + 1) == CELL_HEIGHT_AMOUNT)
			return{ { w - 1, h },{ w - 1, h - 1 },{ w, h - 1 } }; // down side
	}
}
Engine::Neighbours Engine::PentaRight(unsigned w, unsigned h, Map& map)
{
	if (w != 0 && (w + 1) != CELL_WIDTH_AMOUNT && h != 0 && (h + 1) != CELL_HEIGHT_AMOUNT) // all others
		return{ { w, h - 1 },{ w + 1, h - 1 },{ w + 1, h },{ w + 1, h + 1 },{ w, h + 1 } };

	if (w == 0)
	{
		if (h == 0)				   return{ { w + 1, h },{ w + 1, h + 1 },{ w, h + 1 } }; // upper-left corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w + 1, h },{ w + 1, h - 1 },{ w, h - 1 } }; // down-left corner
		return{ { w, h - 1 },{ w, h + 1 },{ w + 1, h - 1 },{ w + 1, h },{ w + 1, h + 1 } }; // left side
	}

	if ((w + 1) == CELL_WIDTH_AMOUNT)
	{
		if (h == 0)				   return{ { w, h + 1 } }; // upper-right corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w, h - 1 } }; // down-right corner
		return{ { w, h - 1 },{ w, h + 1 } }; // right side
	}
	else
	{
		if (h == 0) return{ { w + 1, h },{ w, h + 1 },{ w + 1, h + 1 } }; // upper side
		if ((h + 1) == CELL_HEIGHT_AMOUNT)
			return{ { w + 1, h },{ w, h - 1 },{ w + 1, h - 1 } }; // down side
	}
}
Engine::Neighbours Engine::PentaUp(unsigned w, unsigned h, Map& map)
{
	if (w != 0 && (w + 1) != CELL_WIDTH_AMOUNT && h != 0 && (h + 1) != CELL_HEIGHT_AMOUNT) // all others
		return{ { w - 1, h - 1 },{ w, h - 1 },{ w + 1, h - 1 },{ w + 1, h },{ w - 1, h } };

	if (w == 0)
	{
		if (h == 0)				   return{ { w + 1, h } }; // upper-left corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w + 1, h },{ w + 1, h - 1 },{ w, h - 1 } }; // down-left corner
		return{ { w, h - 1 },{ w + 1, h - 1 },{ w + 1, h } }; // left side
	}

	if ((w + 1) == CELL_WIDTH_AMOUNT)
	{
		if (h == 0)				   return{ { w - 1, h } }; // upper-right corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w, h - 1 },{ w - 1, h - 1 },{ w - 1, h } }; // down-right corner
		return{ { w, h - 1 },{ w - 1, h - 1 },{ w - 1, h } }; // right side
	}
	else
	{
		if (h == 0) return{ { w - 1, h },{ w + 1, h } }; // upper side
		if ((h + 1) == CELL_HEIGHT_AMOUNT)
			return{ { w - 1, h },{ w + 1, h },{ w - 1, h - 1 },{ w, h - 1 },{ w + 1, h - 1 } }; // down side
	}
}
Engine::Neighbours Engine::PentaDown(unsigned w, unsigned h, Map& map)
{
	if (w != 0 && (w + 1) != CELL_WIDTH_AMOUNT && h != 0 && (h + 1) != CELL_HEIGHT_AMOUNT) // all others
		return{ { w + 1, h },{ w + 1, h + 1 },{ w, h + 1 },{ w - 1, h + 1 },{ w - 1, h } };

	if (w == 0)
	{
		if (h == 0)				   return{ { w + 1, h },{ w + 1, h + 1 },{ w, h + 1 } }; // upper-left corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w + 1, h } }; // down-left corner
		return{ { w, h + 1 },{ w + 1, h },{ w + 1, h + 1 } }; // left side
	}

	if ((w + 1) == CELL_WIDTH_AMOUNT)
	{
		if (h == 0)				   return{ { w - 1, h },{ w - 1, h + 1 },{ w, h + 1 } }; // upper-right corner
		if ((h + 1) == CELL_HEIGHT_AMOUNT) return{ { w - 1, h } }; // down-right corner
		return{ { w, h + 1 },{ w - 1, h },{ w - 1, h + 1 } }; // right side
	}
	else
	{
		if (h == 0) return{ { w - 1, h },{ w + 1, h },{ w - 1, h + 1 },{ w, h + 1 },{ w + 1, h + 1 } }; // upper side
		if ((h + 1) == CELL_HEIGHT_AMOUNT)
			return{ { w - 1, h },{ w + 1, h } }; // down side
	}
}
Engine::Neighbours Engine::PentaRandom(unsigned w, unsigned h, Map& map)
{
	int random = rand() % 4;
	if (random == 0) 
		return PentaLeft(w, h, map);
	if (random == 1)
		return PentaRight(w, h, map);
	if (random == 2)
		return PentaUp(w, h, map);
	if (random == 3)
		return PentaDown(w, h, map);
}

Engine::Neighbours Engine::getNeighbours(unsigned w, unsigned h, Map& map, NeighbourType neighbour_type, BoundaryCondition boundary_condition)
{
	if (boundary_condition == BoundaryCondition::Periodic) // goes through boundaries
	{
		switch (neighbour_type)
		{
		case NeighbourType::Moore:
			return PeriodicMoore(w, h, map);
		case NeighbourType::Neumann:
			return PeriodicNeumann(w, h, map);
		case NeighbourType::HexLeft:
			return PeriodicHexLeft(w, h, map);
		case NeighbourType::HexRight:
			return PeriodicHexRight(w, h, map);
		case NeighbourType::HexRandom:
			return PeriodicHexRandom(w, h, map);
		case NeighbourType::PentaRandom:
			return PeriodicPentaRandom(w, h, map);
		}
	}
	else
	{
		switch (neighbour_type)
		{
		case NeighbourType::Moore:
			return Moore(w, h, map);
		case NeighbourType::Neumann:
			return Neumann(w, h, map);
		case NeighbourType::HexLeft:
			return HexLeft(w, h, map);
		case NeighbourType::HexRight:
			return HexRight(w, h, map);
		case NeighbourType::HexRandom:
			return HexRandom(w, h, map);
		case NeighbourType::PentaRandom:
			return PentaRandom(w, h, map);
		}
	}
}