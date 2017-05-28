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
	void resetGraphicMap();
	void displayWindow(std::unique_ptr<sf::RenderWindow>& window);
	void displayResult(std::unique_ptr<sf::RenderWindow>& window);
	void initializeGraphicMap(const Map& map, std::unique_ptr<sf::RenderWindow>& window, Games choosed_game);
	void updateGraphicCell(int i, int j, int color, std::unique_ptr<sf::RenderWindow>& window);
	void drawMap(std::unique_ptr<sf::RenderWindow>& window);
	void drawCell(sf::RectangleShape& cell, std::unique_ptr<sf::RenderWindow>& window);
	bool lookForInput(int x, int y, std::unique_ptr<sf::RenderWindow>& window, bool allowSwipe);
	bool listenToGUI(std::vector<GUIObject>& GUI, std::unique_ptr<sf::RenderWindow>& window);
	void drawGUIonScreen(std::vector<GUIObject> GUI, std::unique_ptr<sf::RenderWindow>& window);

private:
	bool lookForInput(GUIObject gui_object, std::unique_ptr<sf::RenderWindow>& window);
	std::vector<std::vector<sf::RectangleShape>> cells_representation;
	std::vector<MyColor> colors;
	void createColors();
};