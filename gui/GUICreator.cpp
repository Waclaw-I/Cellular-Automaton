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
	GUI.push_back(GUIButton(410, 300, TexturesHolder::buttons["exit"], callback, 1, 1));
	GUI.back().setCallback([&game_conditions]() { game_conditions.choosed_game = Games::Exit; });

	return GUI;
}


std::vector<GUIObject> GUICreator::createSeedsGrowthStartGUI()
{
	auto& callback = []() { std::cout << "Nacisnieto" << std::endl; }; // blank function
	std::vector<GUIObject> GUI;
	GUI.push_back(GUIButton(650, 400, TexturesHolder::buttons["start"], callback, 1, 1));

	return GUI;

}

std::vector<GUIObject> GUICreator::createSeedsGrowthUpdateGUI()
{
	auto& callback = []() {};
	std::vector<GUIObject> GUI;
	GUI.push_back(GUIButton(600, 10, TexturesHolder::buttons["start"], callback, 1, 1));
	GUI.push_back(GUIButton(600, 110, TexturesHolder::buttons["pause"], callback, 1, 1));
	GUI.push_back(GUIButton(600, 210, TexturesHolder::buttons["resume"], callback, 1, 1));

	return GUI;

}
//std::vector<GUIObject> GUICreator::createGameOfLifeGUI()
//{
//
//}