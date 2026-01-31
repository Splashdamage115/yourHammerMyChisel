#pragma once

#include "Library.h"

struct BookPixels
{
	std::vector<sf::RectangleShape> m_pixels;
	std::vector<bool> drawn;
	sf::RectangleShape collisionBox;
	sf::RectangleShape shadow;
	void setNewPositionOffset(sf::Vector2f t_newVector);
	bool colliding();
	void drawPixel();
};

class Book
{
public:
	void Start();
	void Update();
	void Render(sf::RenderWindow& t_window);
private:
	bool mouseDown = false;
	bool dragging = false;
	bool held = false;
	BookPixels m_book;
	sf::Vector2f m_lastMousePosition;
};

