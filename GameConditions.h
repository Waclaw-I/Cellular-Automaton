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
	Games choosed_game;
	GameState game_state;
	void setGameToUpdate() { game_state = GameState::Update; }
	void setGameToStart() { game_state = GameState::Start; }
	void setGameToPause() { game_state = GameState::Pause; }
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