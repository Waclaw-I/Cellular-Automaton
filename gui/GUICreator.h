#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include "GUIObject.h"
#include "../GameConditions.h" // TODO: make a non direct path
#include "../Engine.h"
#include "../CellPopulator.h"

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
	std::vector<GUIObject> createSeedsGrowthStartGUI(GameConditions& game_conditions,
		Map& game_map,
		Engine& engine,
		CellPopulator& cell_populator,
		Displayer& displayer,
		std::unique_ptr<sf::RenderWindow>& window);
	std::vector<GUIObject> createGameOfLifeStartGUI(GameConditions& game_conditions);
	std::vector<GUIObject> createGameOfLifeUpdateGUI(GameConditions& game_conditions);
private:

};