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
	std::vector<GUIObject> createPeriodicSettingsGUI(GameConditions& game_conditions);
	std::vector<GUIObject> createNeighbourhoodSettingsGUI(GameConditions& game_conditions);
	std::vector<GUIObject> createSeedsGrowthUpdateGUI(GameConditions& game_conditions);
	std::vector<GUIObject> createSeedsGrowthStartGUI(GameConditions& game_conditions);
	std::vector<GUIObject> createGameOfLifeStartGUI(GameConditions& game_conditions);
	std::vector<GUIObject> createGameOfLifeUpdateGUI(GameConditions& game_conditions);
private:

};