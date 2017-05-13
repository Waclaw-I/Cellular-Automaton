#pragma once
#include "Resources.h"
#include <memory>
#include <SFML/Graphics.hpp>

class Displayer
{
public:
	Displayer();

	void clearWindow(std::unique_ptr<sf::RenderWindow>& window);
	void displayWindow(std::unique_ptr<sf::RenderWindow>& window);
	void drawMap(const Map& map, std::unique_ptr<sf::RenderWindow>& window);
	bool lookForInput(int x, int y, std::unique_ptr<sf::RenderWindow>& window);

private:
	std::vector<std::vector<sf::RectangleShape>> cells_representation;
	std::vector<MyColor> colors;
	void createColors();
};