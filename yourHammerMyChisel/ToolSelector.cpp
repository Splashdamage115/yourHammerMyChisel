#include "ToolSelector.h"
#include "GamePlay.h"
#include "Game.h"

void ToolSelector::Start(Tool t_toolType, sf::Vector2f t_startPos)
{
	m_NewToolType = t_toolType;
	body.setSize(sf::Vector2f(150.f, 225.f));
	body.setFillColor(sf::Color(0.f, 0.f, 0.f, 125.f));
	body.setPosition(t_startPos);
	
	
}

void ToolSelector::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		mouseDown = true;
	}
	else
	{
		if (mouseDown == true)
		{
			// mouse just released
			if (body.getGlobalBounds().contains(Game::mousePosition))
			{
				DEBUG_MSG("NEW TOOL SELECTED");
				GamePlay::heldTool = (GamePlay::heldTool == Tool::none) ? m_NewToolType : Tool::none;
				if (GamePlay::heldTool == Tool::none)
				{
					sf::Cursor c = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
					Game::getInstance().m_window.setMouseCursor(c);	
				}
				else
				{
					sf::Cursor selected = sf::Cursor::createFromSystem((GamePlay::heldTool == Tool::Chisel) ? sf::Cursor::Type::Cross : sf::Cursor::Type::Help).value();
					Game::getInstance().m_window.setMouseCursor(selected);
				}
			}
		}
		mouseDown = false;
	}
}

void ToolSelector::Render(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}
