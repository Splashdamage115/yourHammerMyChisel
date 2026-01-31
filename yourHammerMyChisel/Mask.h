#pragma once

#include "Library.h"

struct MaskPixel
{
	sf::RectangleShape pixel;
	sf::RectangleShape shadow;

	bool checkMouse();
	void setNewPositionOffset(sf::Vector2f t_newVector);

	static sf::Color maskColor;

	bool cut = false;
};

struct maskStruct
{
	bool operator==(const maskStruct& t_rhs);

	std::vector<MaskPixel> m_pixels;

	void update();

	void initMask();
	void renderMask(sf::RenderWindow& t_window);

private:
	sf::Vector2f lastMousePos = { 0.f,0.f };
	bool mouseDown = false;
};

class Mask
{
public:
	void Start();
	void update();
	void Render(sf::RenderWindow& t_window);
private:
	maskStruct editableMask;

	std::vector<maskStruct> savedMasks;
};

