#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include <functional>

// try to create whole SFML - button library for later usage. ll be needed!
enum class GUIObjectStates // remember about YAGNI! To be implemented later on (graphic changes with different interactions)
{
	NORMAL,
	ACTIVE,
	PUSHED,
	HOVERED,
	DISABLED
};

class GUIObject
{
public:
	sf::Sprite sprite;
	GUIObject(sf::Texture& texture);

	void setPosition(int x, int y);
	void setScale(double scale_x, double scale_y); // in order to modify sprites

	int getX();
	int getY();
	double getScale_x();
	double getScale_y();
	int get_width();
	int get_height();
	void onClick();
	void setCallback(std::function<void()> callback);


protected:
	std::vector<sf::Sprite> sprite_states;
	int x;
	int y;
	double scale_x;
	double scale_y;
	std::function<void()> callback;


	void updateSprite();
};