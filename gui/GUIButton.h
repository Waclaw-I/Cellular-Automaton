#pragma once
#include "GUIObject.h"
class GUIButton : public GUIObject
{
public:

	GUIButton(int x, int y, sf::Texture& texture, std::function<void()> callback, double scale_x, double scale_y);
};