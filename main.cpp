#include <iostream>

#include <SFML\Graphics.hpp>

#include "MapGenerator.h"
#include "GameConditions.h"
#include "Displayer.h"
#include "CellPopulator.h"
#include "Engine.h"

using namespace std;


MapGenerator map_generator;
CellPopulator cell_populator;

GameConditions game_conditions;
Games GameConditions::choosed_game = Games::SeedsGrowth;

SeedsGrowthConditions seeds_growth_conditions;
GameOfLifeConditions game_of_life_conditions;
Displayer displayer;
Engine engine;


int main()
{
	srand(time(NULL));
	game_conditions.game_state = GameState::Start;

	seeds_growth_conditions.seed_randomization = SeedRandomization::Clicked;
	seeds_growth_conditions.boundary_condition = BoundaryCondition::Periodic;
	seeds_growth_conditions.neighbour_type = NeighbourType::PentaRandom;
	game_of_life_conditions.cells_initialization = CellsInitialization::Clicked;

	auto window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
	Map game_map = map_generator.createNewMap(MAP_WIDTH, MAP_HEIGHT);


	while (game_conditions.choosed_game == Games::GameOfLife)
	{
		while (game_conditions.game_state == GameState::Start)
		{
			if (game_of_life_conditions.cells_initialization == CellsInitialization::Clicked)
			{
				cell_populator.addCellByClick(game_map, displayer, window);
				if (CellPopulator::ACTUAL_GROUP == 5) //CREATE A START BUTTON
				{
					game_of_life_conditions.cells_initialization = CellsInitialization::Done;
					game_conditions.game_state = GameState::Update;
				}
			}
			displayer.clearWindow(window);
			displayer.drawMap(game_map, window);
			displayer.displayWindow(window);
		}

		while (game_conditions.game_state == GameState::Update)
		{
			displayer.clearWindow(window);
			GameData::map_history.push_back(engine.designateNextFrame(game_map));
			game_map = GameData::map_history.back();
			displayer.drawMap(game_map, window);
			displayer.displayWindow(window);
			engine.Wait();

		}
	}
	

	while (game_conditions.choosed_game == Games::SeedsGrowth)
	{
		while (game_conditions.game_state == GameState::Start)
		{
			if (seeds_growth_conditions.seed_randomization == SeedRandomization::Clicked)
			{
				cell_populator.addCellByClick(game_map, displayer, window);
				if (CellPopulator::ACTUAL_GROUP == 10)
				{
					seeds_growth_conditions.seed_randomization = SeedRandomization::Done;
					game_conditions.game_state = GameState::Update;
				}
			}
			displayer.clearWindow(window);
			displayer.drawMap(game_map, window);
			displayer.displayWindow(window);
		}

		while (game_conditions.game_state == GameState::Update)
		{
			engine.Wait();
			displayer.clearWindow(window);
			displayer.drawMap(game_map, window);
			displayer.displayWindow(window);
			GameData::map_history.push_back(engine.makeSeedsGrow(game_map,
															     seeds_growth_conditions.neighbour_type,
																 seeds_growth_conditions.boundary_condition));
			game_map = GameData::map_history.back();
			
			
		}
	}


	std::cin.get();
}