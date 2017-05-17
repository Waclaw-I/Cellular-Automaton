#pragma once
#include "Resources.h"

enum class Games
{
	MainMenu,
	GameOfLife,
	SeedsGrowth,
	Exit
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
	None
};

enum class BoundaryCondition
{
	Periodic,
	Unperiodic,
	None
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
	Games choosed_game;
	GameState game_state;
	CellsInitialization cells_initialization;
	SeedRandomization seed_randomization;
	BoundaryCondition boundary_condition;
	NeighbourType neighbour_type;
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