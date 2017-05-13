#pragma once

enum class Games
{
	GameOfLife,
	SeedsGrowth
};

enum class GameState
{
	Start,
	Update,
	Pause
};

enum class NeighbourType
{
	Neumann,
	Moore,
	HexLeft,
	HexRight,
	HexRandom,
	PentaRandom,
};

enum class BoundaryCondition
{
	Periodic,
	Unperiodic
};

enum class SeedRandomization
{
	Random,
	Equal,
	Random_R,
	Clicked,
	Done

};

enum class CellsInitialization
{
	Random,
	Clicked,
	Glider,
	Dacota,
	Done
};

namespace GameData
{
	static std::vector<Map> map_history;
	static bool MousePressed = false;
	static double game_speed = 8.0;
}

struct GameConditions
{
	static Games choosed_game;
	GameState game_state;
};

struct GameOfLifeConditions
{
	CellsInitialization cells_initialization;
};

struct SeedsGrowthConditions
{
	NeighbourType neighbour_type;
	BoundaryCondition boundary_condition;
	SeedRandomization seed_randomization;
};