#pragma once

#include "Library.h"

class Book
{
public:
	void Start();
	void Update();
	void Render(sf::RenderWindow& t_window);
private:
	bool mouseDown = false;
};

