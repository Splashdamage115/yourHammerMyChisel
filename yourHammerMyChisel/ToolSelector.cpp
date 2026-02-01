#include "ToolSelector.h"
#include "GamePlay.h"
#include "Game.h"

ToolSelector::ToolSelector() : body(t)
{
}

void ToolSelector::Start(Tool t_toolType, sf::Vector2f t_startPos)
{
	m_NewToolType = t_toolType;

	std::string address = "";

	switch (t_toolType)
	{
	case Tool::none:
		break;
	case Tool::Chisel:
		address = "ASSETS\\IMAGES\\table_hammer.png";
		break;
	case Tool::Brush:
		address = "ASSETS\\IMAGES\\table_feather.png";
		break;
	default:
		break;
	}
	if (!t.loadFromFile(address))
	{
		std::cout << "ERROR: Can't load 'startbutton.png" << std::endl;
	}
	body.setTexture(t);
	body.setTextureRect(sf::IntRect{ sf::Vector2i{0,0}, sf::Vector2i{static_cast<int>(t.getSize().x),static_cast<int>(t.getSize().y)}});
	body.setScale(sf::Vector2f{ 4.0f,4.0f });
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
