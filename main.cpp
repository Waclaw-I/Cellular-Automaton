#include <iostream>
#include <math.h>
#include <SFML\Graphics.hpp>

#include "MapGenerator.h"
#include "GameConditions.h"
#include "Displayer.h"
#include "CellPopulator.h"
#include "Engine.h"
#include "gui/GUICreator.h"
#include "FileReader.h"


using namespace std;

FileReader file_reader("settings.txt");



int main()
{
	MapGenerator map_generator;
	GUICreator GUI_creator;
	CellPopulator cell_populator;
	SeedsGrowthConditions seeds_growth_conditions;
	GameOfLifeConditions game_of_life_conditions;
	Displayer displayer;
	Engine engine;

	TexturesHolder::loadTextures();
	srand(time(NULL));
	GameConditions game_conditions;
	game_conditions.game_state = GameState::Start;
	game_conditions.choosed_game = Games::MainMenu;
	game_conditions.boundary_condition = BoundaryCondition::None;
	game_conditions.neighbour_type = NeighbourType::None;
	seeds_growth_conditions.seed_randomization = SeedRandomization::Clicked;
	seeds_growth_conditions.boundary_condition = BoundaryCondition::None;
	seeds_growth_conditions.neighbour_type = NeighbourType::None;
	game_of_life_conditions.cells_initialization = CellsInitialization::Clicked;
	Map game_map = map_generator.createNewMap(CELL_WIDTH_AMOUNT, CELL_HEIGHT_AMOUNT);

	while (game_conditions.choosed_game != Games::Exit)
	{

		auto window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
		std::vector<GUIObject> main_menu_GUI = GUI_creator.createMainMenuGUI(game_conditions);

		while (game_conditions.choosed_game == Games::MainMenu)
		{
			displayer.clearWindow(window);
			displayer.drawGUIonScreen(main_menu_GUI, window);
			displayer.displayWindow(window);
			displayer.listenToGUI(main_menu_GUI, window);
		}
		std::vector<GUIObject> boundary_GUI = GUI_creator.createPeriodicSettingsGUI(game_conditions);
		while (game_conditions.boundary_condition == BoundaryCondition::None && game_conditions.choosed_game != Games::MainMenu && game_conditions.choosed_game != Games::Exit)
		{
			displayer.clearWindow(window);
			displayer.drawGUIonScreen(boundary_GUI, window);
			displayer.displayWindow(window);
			displayer.listenToGUI(boundary_GUI, window);
		}

		bool randomized = false;
		while (game_conditions.choosed_game == Games::MonteCarlo && game_conditions.boundary_condition != BoundaryCondition::None)
		{

			std::vector<GUIObject> neighbourhood_GUI = GUI_creator.createNeighbourhoodSettingsGUI(game_conditions);
			while (game_conditions.neighbour_type == NeighbourType::None && game_conditions.boundary_condition != BoundaryCondition::None)
			{
				displayer.clearWindow(window);
				displayer.drawGUIonScreen(neighbourhood_GUI, window);
				displayer.displayWindow(window);
				displayer.listenToGUI(neighbourhood_GUI, window);
			}
			
			if (!randomized)
			{

				cell_populator.randomizeMap(game_map, displayer, window, monte_carlo_groups); // groups amount
				displayer.initializeGraphicMap(game_map, window, game_conditions.choosed_game);
				randomized = true;
			}

			std::vector<GUIObject> start_GUI = GUI_creator.createGameOfLifeStartGUI(game_conditions);
			std::vector<GUIObject> stop_GUI = GUI_creator.createPauseGUI(game_conditions);
			while (game_conditions.game_state == GameState::Start)
			{
				displayer.clearWindow(window);
				displayer.drawMap(window);
				displayer.drawGUIonScreen(start_GUI, window);
				displayer.listenToGUI(start_GUI, window);
				displayer.displayWindow(window);
			}

			while (game_conditions.game_state == GameState::Update)
			{
				
				engine.energize(game_map, game_conditions.neighbour_type, game_conditions.boundary_condition);
				while (true)
				{
					int random_i = rand() % CELL_HEIGHT_AMOUNT;
					int random_j = rand() % CELL_WIDTH_AMOUNT;
					engine.energizeOne(game_map, game_conditions.neighbour_type, game_conditions.boundary_condition, random_i, random_j, monte_carlo_groups);
					displayer.updateGraphicCell(random_i, random_j, game_map[random_i][random_j].group, window);
					displayer.drawGUIonScreen(stop_GUI, window);
					displayer.listenToGUI(stop_GUI, window);
					displayer.displayWindow(window);
					if (game_conditions.choosed_game == Games::Exit)
					{
						auto result_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT), "Result");
						while (true)
						{
							displayer.displayResult(result_window);
							displayer.displayWindow(result_window);
						}
							

					}
				}
			}
		}

		while (game_conditions.choosed_game == Games::GameOfLife)
		{
			game_conditions.neighbour_type = NeighbourType::Moore; // only viable for Game of Life
			std::vector<GUIObject> start_GUI = GUI_creator.createGameOfLifeStartGUI(game_conditions);
			
			while (game_conditions.game_state == GameState::Start)
			{
				cell_populator.addCellByClick(game_map, displayer, window, true);

				displayer.clearWindow(window);
				displayer.drawMap(window);
				displayer.drawGUIonScreen(start_GUI, window);
				displayer.displayWindow(window);
				displayer.listenToGUI(start_GUI, window);
			}

			while (game_conditions.game_state == GameState::Update)
			{
				displayer.clearWindow(window);
				GameData::map_history.push_back(engine.designateNextFrame(game_map, game_conditions.neighbour_type, game_conditions.boundary_condition));
				game_map = GameData::map_history.back();
				displayer.initializeGraphicMap(game_map, window, game_conditions.choosed_game);
				displayer.drawMap(window);
				displayer.displayWindow(window);
				engine.Wait();

			}
		}

		while (game_conditions.choosed_game == Games::SeedsGrowth && game_conditions.boundary_condition != BoundaryCondition::None)
		{

			std::vector<GUIObject> neighbourhood_GUI = GUI_creator.createNeighbourhoodSettingsGUI(game_conditions);
			while (game_conditions.neighbour_type == NeighbourType::None && game_conditions.boundary_condition != BoundaryCondition::None)
			{
				displayer.clearWindow(window);
				displayer.drawGUIonScreen(neighbourhood_GUI, window);
				displayer.displayWindow(window);
				displayer.listenToGUI(neighbourhood_GUI, window);
			}

			std::vector<GUIObject> start_GUI = GUI_creator.createSeedsGrowthStartGUI(game_conditions, game_map, engine, cell_populator, displayer, window);
			while (game_conditions.game_state == GameState::Start &&
				   game_conditions.boundary_condition != BoundaryCondition::None &&
				   game_conditions.choosed_game != Games::Exit)
			{
				if (game_conditions.seed_randomization == SeedRandomization::Clicked)
				{
					cell_populator.addCellByClick(game_map, displayer, window, false);
				}
				displayer.clearWindow(window);
				displayer.drawMap(window);
				displayer.drawGUIonScreen(start_GUI, window);
				displayer.displayWindow(window);
				displayer.listenToGUI(start_GUI, window);
			}

			while (game_conditions.game_state == GameState::Update)
			{
				engine.Wait();
				displayer.clearWindow(window);
				displayer.drawMap(window);
				displayer.displayWindow(window);
				GameData::map_history.push_back(engine.makeSeedsGrow(game_map,
					game_conditions.neighbour_type,
					game_conditions.boundary_condition));
				game_map = GameData::map_history.back();
				displayer.initializeGraphicMap(game_map, window, game_conditions.choosed_game);
				if (engine.isMapFull(game_map)) game_conditions.game_state = GameState::Crystallization;
			}

			
			
			unsigned time = 1;
			while (game_conditions.game_state == GameState::Crystallization)
			{
				previous_Ro = Ro;
				Ro = (A / B) + (1 - (A / B)) * std::pow(e, -B * (time / 1000.0));

				for (int i = 0; i < CELL_HEIGHT_AMOUNT; ++i)
				{
					for (int j = 0; j < CELL_WIDTH_AMOUNT; ++j)
					{
						auto deltaRo = Ro - game_map[i][j].my_ro;
						double tempRo = deltaRo / static_cast<double>(CELL_AMOUNT);

						game_map[i][j].my_ro = tempRo;

						if (!game_map[i][j].crystalized)
						{
							if (engine.isCellOnEdge(game_map, i, j,
								game_conditions.neighbour_type,
								game_conditions.boundary_condition))
							{
								game_map[i][j].my_ro = tempRo * 0.8;
								leftover_Ro += tempRo * 0.2;
							}
							else
							{
								game_map[i][j].my_ro = tempRo * 0.2;
								leftover_Ro += tempRo * 0.8;
							}
						}
					}
				}
				auto ro_to_add = static_cast<double>(leftover_Ro / k);
				int random_cells_amount = rand() % CELL_AMOUNT + 1;
				for (int i = 0; i < random_cells_amount; ++i)
				{
					int random_i = rand() % CELL_HEIGHT_AMOUNT;
					int random_j = rand() % CELL_WIDTH_AMOUNT;

					if (engine.isCellOnEdge(game_map, random_i, random_j,
						game_conditions.neighbour_type,
						game_conditions.boundary_condition))
					{
						game_map[random_i][random_j].my_ro += ro_to_add;
					}
				}

				for (int i = 0; i < CELL_HEIGHT_AMOUNT; ++i)
				{
					for (int j = 0; j < CELL_WIDTH_AMOUNT; ++j)
					{
						if (game_map[i][j].isRoExceeded() && !game_map[i][j].crystalized)
						{
							game_map[i][j].crystalized = true;
							game_map[i][j].group = rand() % MAX_GROUPS;
							game_map[i][j].my_ro = 0;
						}
					}
				}

				displayer.clearWindow(window);
				displayer.initializeGraphicMap(game_map, window, game_conditions.choosed_game);
				displayer.drawMap(window);
				displayer.displayWindow(window);
				engine.Wait();
				
				GameData::map_history.push_back(engine.crystalize(game_map,
					game_conditions.neighbour_type,
					game_conditions.boundary_condition));

				game_map = GameData::map_history.back();
				
			}
			
		}

	}
}