#pragma once

#include "Library.h"

enum class Tool;

class ToolSelector
{
public:
	ToolSelector() {}
	void Start(Tool t_toolType, sf::Vector2f t_startPos);
	void Update();
	void Render(sf::RenderWindow& t_window);
private:
	sf::RectangleShape body;
	bool mouseDown = false;
	Tool m_NewToolType;
	//sf::Cursor m_selectedType;
};

