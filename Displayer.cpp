#include "Displayer.h"
#include <iostream>

Displayer::Displayer()
{
	createColors();
	sf::RectangleShape model_rect;
	model_rect.setSize(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
	model_rect.setFillColor(sf::Color::White);
	model_rect.setOutlineColor(sf::Color::Black);
	model_rect.setOutlineThickness(1);

	cells_representation = std::vector<std::vector<sf::RectangleShape>>(CELL_HEIGHT_AMOUNT);
	for (auto& row : cells_representation)
		row = std::vector<sf::RectangleShape>(CELL_WIDTH_AMOUNT);

	for (int i = 0; i < cells_representation.size(); ++i)
	{
		auto&& row_size = cells_representation[i].size();
		for (int j = 0; j < row_size; ++j)
		{
			cells_representation[i][j] = model_rect;
			cells_representation[i][j].setPosition(CELL_HEIGHT * i, CELL_WIDTH * j);
		}
	}
}

void Displayer::createColors()
{
	for (int i = 1; i <= MAX_GROUPS; ++i)
	{
		MyColor color = { rand() % 255, rand() % 255, rand() % 255 };
		colors.push_back( color );
	}
}

void Displayer::clearWindow(std::unique_ptr<sf::RenderWindow>& window)
{
	window->clear(sf::Color::White);
}
void Displayer::displayWindow(std::unique_ptr<sf::RenderWindow>& window)
{
	window->display();
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Displayer::drawMap(const Map& map, std::unique_ptr<sf::RenderWindow>& window, Games choosed_game)
{
	for (int i = 0; i < map.size(); ++i)
	{
		auto&& row_size = map[i].size();
		for (int j = 0; j < row_size; ++j)
		{
			if (choosed_game == Games::SeedsGrowth)
			{

				if (map[i][j].alive)
				{ 
					cells_representation[i][j].setFillColor(sf::Color(colors[map[i][j].group][0],
																	  colors[map[i][j].group][1],
																	  colors[map[i][j].group][2]));
				}
				else
				{
					cells_representation[i][j].setFillColor(sf::Color::White);
				}
			}
			else
			{
				if (map[i][j].alive)
					cells_representation[i][j].setFillColor(sf::Color::Green);
				else
					cells_representation[i][j].setFillColor(sf::Color::White);
			}
		}
	}
	for (auto& row : cells_representation)
		for (auto& cell : row)
		{
			window->draw(cell);
		}
}

bool Displayer::lookForInput(int x, int y , std::unique_ptr<sf::RenderWindow>& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && GameData::MousePressed)
		return false;
	else
		GameData::MousePressed = false;

	int mouse_x = sf::Mouse::getPosition(*window).x;
	int mouse_y = sf::Mouse::getPosition(*window).y;
	auto& cell = cells_representation[x][y];

	int cell_x = cell.getPosition().x;
	int cell_y = cell.getPosition().y;
	if (mouse_x > cell_x && mouse_x < cell_x + cell.getSize().x &&
		mouse_y > cell_y && mouse_y < cell_y + cell.getSize().y &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		GameData::MousePressed == false)
	{
		GameData::MousePressed = true;
		return true;
	}
	return false;
}

bool Displayer::lookForInput(GUIObject gui_object, std::unique_ptr<sf::RenderWindow>& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && GameData::MousePressed)
		return false;
	else
		GameData::MousePressed = false;

	int mouse_x = sf::Mouse::getPosition(*window).x;
	int mouse_y = sf::Mouse::getPosition(*window).y;

	int gui_object_x = gui_object.getX();
	int gui_object_y = gui_object.getY();
	if (mouse_x > gui_object_x && mouse_x < gui_object_x + gui_object.get_width() &&
		mouse_y > gui_object_y && mouse_y < gui_object_y + gui_object.get_height() &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		GameData::MousePressed == false)
	{
		GameData::MousePressed = true;
		return true;
	}
	return false;
}
void Displayer::drawGUIonScreen(std::vector<GUIObject> GUI, std::unique_ptr<sf::RenderWindow>& window)
{
	for (auto& gui_object : GUI)
	{
		window->draw(gui_object.sprite);
	}
}