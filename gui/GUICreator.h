#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include "GUIObject.h"
#include "../GameConditions.h" // TODO: make a non direct path

struct TexturesHolder
{
public:

	static bool loadTextures();
	static std::map<std::string, sf::Texture> buttons;
};

class GUICreator
{
public:
	std::vector<GUIObject> createMainMenuGUI(GameConditions& game_conditions);
	std::vector<GUIObject> createSeedsGrowthUpdateGUI();
	std::vector<GUIObject> createSeedsGrowthStartGUI();
	std::vector<GUIObject> createGameOfLifeStartGUI();
	std::vector<GUIObject> createGameOfLifeUpdateGUI();
private:

};