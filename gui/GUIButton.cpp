#include "GUIButton.h"

GUIButton::GUIButton(int x, int y, sf::Texture& texture, std::function<void()> callback, double scale_x, double scale_y)
	: GUIObject(texture)
{
	this->x = x;
	this->y = y;
	this->callback = callback; // should be moved to the GUIObject
	this->scale_x = scale_x;
	this->scale_y = scale_y;

	this->updateSprite();
}

GUIButton::GUIButton(int x, int y, sf::Text, std::function<void()> callback, double scale_x, double scale_y)
{

}