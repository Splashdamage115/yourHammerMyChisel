#pragma once

#include "Library.h"

struct MaskPixel
{
	sf::RectangleShape pixel;

	sf::Color maskColor = sf::Color::White;
};

struct mask
{
	std::vector<MaskPixel> m_pixels;

	void initMask();
	void renderMask(sf::RenderWindow& t_window);
};

class Mask
{
public:
	void Start();
	void update();
	void Render(sf::RenderWindow& t_window);
private:
	mask editableMask;
};

