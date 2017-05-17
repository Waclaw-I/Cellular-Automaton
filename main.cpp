#include <iostream>

#include <SFML\Graphics.hpp>

#include "MapGenerator.h"
#include "GameConditions.h"
#include "Displayer.h"
#include "CellPopulator.h"
#include "Engine.h"
#include "gui/GUICreator.h"

using namespace std;


MapGenerator map_generator;
GUICreator GUI_creator;
CellPopulator cell_populator;


SeedsGrowthConditions seeds_growth_conditions;
GameOfLifeConditions game_of_life_conditions;
Displayer displayer;
Engine engine;


int main()
{
	TexturesHolder::loadTextures();
	srand(time(NULL));
	GameConditions game_conditions;
	game_conditions.game_state = GameState::Start;
	game_conditions.choosed_game = Games::MainMenu;
	game_conditions.boundary_condition = BoundaryCondition::None;
	game_conditions.neighbour_type = NeighbourType::Moore;
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
		while (game_conditions.boundary_condition == BoundaryCondition::None && game_conditions.choosed_game != Games::MainMenu)
		{
			displayer.clearWindow(window);
			displayer.drawGUIonScreen(boundary_GUI, window);
			displayer.displayWindow(window);
			displayer.listenToGUI(boundary_GUI, window);
		}

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
				displayer.drawMap(game_map, window, game_conditions.choosed_game);
				displayer.displayWindow(window);
			}

			while (game_conditions.game_state == GameState::Update)
			{
				displayer.clearWindow(window);
				GameData::map_history.push_back(engine.designateNextFrame(game_map, game_conditions.neighbour_type, game_conditions.boundary_condition));
				game_map = GameData::map_history.back();
				displayer.drawMap(game_map, window, game_conditions.choosed_game);
				displayer.displayWindow(window);
				engine.Wait();

			}
		}

		while (game_conditions.choosed_game == Games::SeedsGrowth)
		{
			std::vector<GUIObject> start_GUI = GUI_creator.createSeedsGrowthStartGUI(game_conditions);
			start_GUI.front().setCallback([&game_conditions]() { game_conditions.setGameToUpdate(); });
			while (game_conditions.game_state == GameState::Start)
			{
				if (seeds_growth_conditions.seed_randomization == SeedRandomization::Clicked)
				{
					cell_populator.addCellByClick(game_map, displayer, window);
					if (CellPopulator::ACTUAL_GROUP == 10)
					{
						//seeds_growth_conditions.seed_randomization = SeedRandomization::Done;
						//game_conditions.game_state = GameState::Update;
					}
				}
				displayer.clearWindow(window);
				displayer.drawMap(game_map, window, game_conditions.choosed_game);
				displayer.drawGUIonScreen(start_GUI, window);
				displayer.displayWindow(window);
				displayer.listenToGUI(start_GUI, window);
			}

			while (game_conditions.game_state == GameState::Update)
			{
				engine.Wait();
				displayer.clearWindow(window);
				displayer.drawMap(game_map, window, game_conditions.choosed_game);
				displayer.displayWindow(window);
				GameData::map_history.push_back(engine.makeSeedsGrow(game_map,
					game_conditions.neighbour_type,
					game_conditions.boundary_condition));
				game_map = GameData::map_history.back();


			}
		}

	}
}