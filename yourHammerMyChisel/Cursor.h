#pragma once

#include "Library.h"

class Cursor
{
public:
	void Start();
	void Update();
	void Render(sf::RenderWindow & t_window);
private:

	sf::Texture cursorTexture;
	sf::Sprite cursorSprite{ cursorTexture };
	
};
