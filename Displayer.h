#pragma once
#include "Resources.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "gui/GUIObject.h"
#include "GameConditions.h"

class Displayer
{
public:
	Displayer();

	void clearWindow(std::unique_ptr<sf::RenderWindow>& window);
	void displayWindow(std::unique_ptr<sf::RenderWindow>& window);
	void drawMap(const Map& map, std::unique_ptr<sf::RenderWindow>& window, Games choosed_game);
	bool lookForInput(int x, int y, std::unique_ptr<sf::RenderWindow>& window);
	bool lookForInput(GUIObject gui_object, std::unique_ptr<sf::RenderWindow>& window);
	void drawGUIonScreen(std::vector<GUIObject> GUI, std::unique_ptr<sf::RenderWindow>& window);

private:
	std::vector<std::vector<sf::RectangleShape>> cells_representation;
	std::vector<MyColor> colors;
	void createColors();
};