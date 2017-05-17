#include "GUIObject.h"

GUIObject::GUIObject(sf::Drawable& texture) :
	sprite(sf::Sprite(texture)),
	scale_x(sprite.getScale().x),
	scale_y(sprite.getScale().y)
{
	x = 0; // is this necessary?
	y = 0; // ...
		   //sprite_states.push_back(sprite);
		   //this->sprite = sprite_states.back();
	setPosition(x, y);
}

void GUIObject::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	sprite.setPosition(x, y);
}

void GUIObject::setScale(double scale_x, double scale_y)
{
	this->scale_x = scale_x;
	this->scale_y = scale_y;
	sprite.setScale(scale_x, scale_y);
}

void GUIObject::updateSprite()
{
	sprite.setPosition(x, y);
	sprite.setScale(scale_x, scale_y);
}

void GUIObject::onClick()
{
	this->callback();
}
void GUIObject::setCallback(std::function<void()> callback)
{
	this->callback = callback;
}


int GUIObject::getX() { return x; }
int GUIObject::getY() { return y; }
double GUIObject::getScale_x() { return scale_x; }
double GUIObject::getScale_y() { return scale_y; }
int GUIObject::get_width() { return this->sprite.getTextureRect().width; }
int GUIObject::get_height() { return this->sprite.getTextureRect().height; }