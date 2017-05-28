#include "GUICreator.h"
#include "GUIButton.h"
#include <iostream>

std::map<std::string, sf::Texture> TexturesHolder::buttons;

bool TexturesHolder::loadTextures()
{
	sf::Texture texture;
	auto& getTexture = [&texture](std::string path)->sf::Texture
	{
		texture.loadFromFile(path);
		texture.setSmooth(true);
		return texture;
	};
	// ADD ALERT IF SOME OF THE TEXTURES WERE NOT LOADED?
	TexturesHolder::buttons["back"] = getTexture("Images/Buttons/b_back.png");
	TexturesHolder::buttons["custom"] = getTexture("Images/Buttons/b_custom.png");
	TexturesHolder::buttons["dacota"] = getTexture("Images/Buttons/b_Dacota.png");
	TexturesHolder::buttons["exit"] = getTexture("Images/Buttons/b_exit.png");
	TexturesHolder::buttons["<<"] = getTexture("Images/Buttons/b_fast_backward.png");
	TexturesHolder::buttons[">>"] = getTexture("Images/Buttons/b_fast_forward.png");
	TexturesHolder::buttons["glider"] = getTexture("Images/Buttons/b_Glider.png");
	TexturesHolder::buttons["load_from_file"] = getTexture("Images/Buttons/b_load_from_file.png");
	TexturesHolder::buttons[">"] = getTexture("Images/Buttons/b_next.png");
	TexturesHolder::buttons["<"] = getTexture("Images/Buttons/b_previous.png");
	TexturesHolder::buttons["resume"] = getTexture("Images/Buttons/b_resume.png");
	TexturesHolder::buttons["save_to_file"] = getTexture("Images/Buttons/b_save_to_file.png");
	TexturesHolder::buttons["seeds_growth"] = getTexture("Images/Buttons/b_seeds_growth.png");
	TexturesHolder::buttons["game_of_life"] = getTexture("Images/Buttons/b_game_of_life.png");
	TexturesHolder::buttons["|<<"] = getTexture("Images/Buttons/b_to_the_beginning.png");
	TexturesHolder::buttons[">>|"] = getTexture("Images/Buttons/b_to_the_end.png");
	TexturesHolder::buttons["pause"] = getTexture("Images/Buttons/b_pause.png");
	TexturesHolder::buttons["start"] = getTexture("Images/Buttons/b_start.png");
	TexturesHolder::buttons["clicked"] = getTexture("Images/Buttons/b_clicked.png");
	TexturesHolder::buttons["equal"] = getTexture("Images/Buttons/b_equal.png");
	TexturesHolder::buttons["hex_left"] = getTexture("Images/Buttons/b_hex_left.png");
	TexturesHolder::buttons["hex_right"] = getTexture("Images/Buttons/b_hex_right.png");
	TexturesHolder::buttons["hex_random"] = getTexture("Images/Buttons/b_hex_random.png");
	TexturesHolder::buttons["moore"] = getTexture("Images/Buttons/b_Moore.png");
	TexturesHolder::buttons["neumann"] = getTexture("Images/Buttons/b_Neumann.png");
	TexturesHolder::buttons["penta_random"] = getTexture("Images/Buttons/b_penta_random.png");
	TexturesHolder::buttons["random"] = getTexture("Images/Buttons/b_random.png");
	TexturesHolder::buttons["random_r"] = getTexture("Images/Buttons/b_random_r.png");
	TexturesHolder::buttons["periodic"] = getTexture("Images/Buttons/b_periodic.png");
	TexturesHolder::buttons["non_periodic"] = getTexture("Images/Buttons/b_non_periodic.png");

	return true;
}

std::vector<GUIObject> GUICreator::createMainMenuGUI(GameConditions& game_conditions)
{
	auto& callback = []() { std::cout << "Nacisnieto" << std::endl; }; // blank function
	std::vector<GUIObject> GUI;
	GUI.push_back(GUIButton(320, 100, TexturesHolder::buttons["game_of_life"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.choosed_game = Games::GameOfLife; });
	GUI.push_back(GUIButton(320, 200, TexturesHolder::buttons["seeds_growth"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.choosed_game = Games::SeedsGrowth; });
	GUI.push_back(GUIButton(320, 300, TexturesHolder::buttons["save_to_file"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.choosed_game = Games::MonteCarlo; });
	GUI.push_back(GUIButton(410, 400, TexturesHolder::buttons["exit"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.choosed_game = Games::Exit; });

	return GUI;
}

std::vector<GUIObject> GUICreator::createGameOfLifeStartGUI(GameConditions& game_conditions)
{
	auto& callback = [&game_conditions]() { game_conditions.game_state = GameState::Update; };
	std::vector<GUIObject> GUI;
	GUI.push_back(GUIButton(650, 400, TexturesHolder::buttons["start"], callback, 1, 1));

	return GUI;
}
std::vector<GUIObject> GUICreator::createGameOfLifeUpdateGUI(GameConditions& game_conditions)
{
	auto& callback = [&game_conditions]() { game_conditions.game_state = GameState::Update; };
	std::vector<GUIObject> GUI;
	GUI.push_back(GUIButton(650, 400, TexturesHolder::buttons["start"], callback, 1, 1));

	return GUI;
}

std::vector<GUIObject> GUICreator::createSeedsGrowthStartGUI(GameConditions& game_conditions,
	Map& game_map,
	Engine& engine,
	CellPopulator& cell_populator,
	Displayer& displayer,
	std::unique_ptr<sf::RenderWindow>& window)
{
	auto random_cells = [&game_map, &window, &engine, &cell_populator, &displayer, &game_conditions]() {
		game_conditions.seed_randomization = SeedRandomization::Random;
		engine.resetMap(game_map);
		displayer.resetGraphicMap();
		cell_populator.addCellByRandom(game_map, displayer, window, MAX_GROUPS);
	};

	auto cells_equally = [&game_map, &window, &engine, &cell_populator, &displayer, &game_conditions]() {
		game_conditions.seed_randomization = SeedRandomization::Equal;
		engine.resetMap(game_map);
		displayer.resetGraphicMap();
		cell_populator.addCellEqually(game_map, displayer, window, MAX_GROUPS);
	};

	auto cells_random_r = [&game_map, &window, &engine, &cell_populator, &displayer, &game_conditions]() {
		game_conditions.seed_randomization = SeedRandomization::Random_R;
		engine.resetMap(game_map);
		displayer.resetGraphicMap();
		cell_populator.addCellRandom_R(game_map, displayer, window, RANGE, game_conditions);
	};
	auto& callback = []() { std::cout << "Nacisnieto" << std::endl; }; // blank function
	std::vector<GUIObject> GUI;
	GUI.push_back(GUIButton(650, 10, TexturesHolder::buttons["start"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.game_state = GameState::Update; });
	GUI.push_back(GUIButton(610, 110, TexturesHolder::buttons["random"], random_cells, 1, 1));
	GUI.push_back(GUIButton(610, 210, TexturesHolder::buttons["clicked"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions, &engine, &game_map, &displayer]() { 
		engine.resetMap(game_map);
		displayer.resetGraphicMap();
		game_conditions.seed_randomization = SeedRandomization::Clicked; });
	GUI.push_back(GUIButton(610, 310, TexturesHolder::buttons["random_r"], cells_random_r, 1, 1));
	GUI.push_back(GUIButton(610, 410, TexturesHolder::buttons["equal"], cells_equally, 1, 1));
	return GUI;

}

std::vector<GUIObject> GUICreator::createSeedsGrowthUpdateGUI(GameConditions& game_conditions)
{
	auto& callback = []() {};
	std::vector<GUIObject> GUI;
	GUI.push_back(GUIButton(600, 10, TexturesHolder::buttons["start"], callback, 1, 1));
	GUI.push_back(GUIButton(600, 110, TexturesHolder::buttons["pause"], callback, 1, 1));
	GUI.push_back(GUIButton(600, 210, TexturesHolder::buttons["resume"], callback, 1, 1));

	return GUI;
}

std::vector<GUIObject> GUICreator::createPeriodicSettingsGUI(GameConditions& game_conditions)
{
	auto& callback = []() {};
	std::vector<GUIObject> GUI;
	GUI.push_back(GUIButton(400, 100, TexturesHolder::buttons["periodic"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.boundary_condition = BoundaryCondition::Periodic; });
	GUI.push_back(GUIButton(375, 200, TexturesHolder::buttons["non_periodic"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.boundary_condition = BoundaryCondition::Unperiodic; });
	GUI.push_back(GUIButton(420, 300, TexturesHolder::buttons["back"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.choosed_game = Games::MainMenu; });

	return GUI;
}
std::vector<GUIObject> GUICreator::createNeighbourhoodSettingsGUI(GameConditions& game_conditions)
{
	auto& callback = []() {};
	std::vector<GUIObject> GUI;
	GUI.push_back(GUIButton(200, 50, TexturesHolder::buttons["neumann"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.neighbour_type = NeighbourType::Neumann; });
	GUI.push_back(GUIButton(210, 150, TexturesHolder::buttons["moore"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.neighbour_type = NeighbourType::Moore; });
	GUI.push_back(GUIButton(160, 250, TexturesHolder::buttons["penta_random"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.neighbour_type = NeighbourType::PentaRandom; });
	GUI.push_back(GUIButton(600, 50, TexturesHolder::buttons["hex_left"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.neighbour_type = NeighbourType::HexLeft; });
	GUI.push_back(GUIButton(600, 150, TexturesHolder::buttons["hex_right"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.neighbour_type = NeighbourType::HexRight; });
	GUI.push_back(GUIButton(600, 250, TexturesHolder::buttons["hex_random"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.neighbour_type = NeighbourType::HexRandom; });

	GUI.push_back(GUIButton(400, 370, TexturesHolder::buttons["back"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.boundary_condition = BoundaryCondition::None; });

	return GUI;
}
//std::vector<GUIObject> GUICreator::createGameOfLifeGUI()
//{
//
//}