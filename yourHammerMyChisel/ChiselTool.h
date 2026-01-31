#pragma once

#include "Library.h"

class ChiselTool
{
public:
	void Start();
	void Update();
	void Render(sf::RenderWindow& t_window);
private:
	sf::RectangleShape body;
	bool mouseDown = false;
};

