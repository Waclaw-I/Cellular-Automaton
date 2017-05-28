#pragma once
#include "Resources.h"
#include "GameConditions.h"

class Engine
{
	using Neighbours = std::vector<std::pair<unsigned, unsigned>>;
public:
	Map designateNextFrame(Map& map, NeighbourType neighbourhood, BoundaryCondition boundary_cond); // GameOfLife
	Map makeSeedsGrow(Map& map, NeighbourType& neighbour_type, BoundaryCondition& boundary_cond);
	Map crystalize(Map& map, NeighbourType& neighbour_type, BoundaryCondition& boundary_cond);
	void resetMap(Map& map);
	bool isMapFull(Map& map);
	bool isCellOnEdge(Map& map, int i, int j, NeighbourType neighbour_type, BoundaryCondition boundary_cond);
	void Wait();

private:
	unsigned getNeighboursAmount(unsigned w, unsigned h, Map& map, Neighbours neighbours);
	Neighbours getNeighbours(unsigned w, unsigned h, Map& map, NeighbourType neighbour_type, BoundaryCondition boundary_condition);

	Neighbours PeriodicMoore(unsigned w, unsigned h, Map& map);
	Neighbours PeriodicNeumann(unsigned w, unsigned h, Map& map);
	Neighbours PeriodicHexLeft(unsigned w, unsigned h, Map& map);
	Neighbours PeriodicHexRight(unsigned w, unsigned h, Map& map);
	Neighbours PeriodicHexRandom(unsigned w, unsigned h, Map& map);
	Neighbours PeriodicPentaRandom(unsigned w, unsigned h, Map& map);

	Neighbours PeriodicPentaLeft(unsigned w, unsigned h, Map& map);
	Neighbours PeriodicPentaRight(unsigned w, unsigned h, Map& map);
	Neighbours PeriodicPentaUp(unsigned w, unsigned h, Map& map);
	Neighbours PeriodicPentaDown(unsigned w, unsigned h, Map& map);

	Neighbours Moore(unsigned w, unsigned h, Map& map);
	Neighbours Neumann(unsigned w, unsigned h, Map& map);
	Neighbours HexLeft(unsigned w, unsigned h, Map& map);
	Neighbours HexRight(unsigned w, unsigned h, Map& map);
	Neighbours HexRandom(unsigned w, unsigned h, Map& map);
	Neighbours PentaRandom(unsigned w, unsigned h, Map& map);

	Neighbours PentaLeft(unsigned w, unsigned h, Map& map);
	Neighbours PentaRight(unsigned w, unsigned h, Map& map);
	Neighbours PentaUp(unsigned w, unsigned h, Map& map);
	Neighbours PentaDown(unsigned w, unsigned h, Map& map);
};