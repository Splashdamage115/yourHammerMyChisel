#include "ChiselTool.h"
#include "GamePlay.h"
#include "Game.h"

void ChiselTool::Start()
{
	body.setSize(sf::Vector2f(150.f, 225.f));
	body.setFillColor(sf::Color(0.f, 0.f, 0.f, 125.f));
	body.setPosition(sf::Vector2f(1700.f, 0.f));
}

void ChiselTool::Update()
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
				GamePlay::heldTool = (GamePlay::heldTool == Tool::none) ? Tool::Chisel : Tool::none;
			}
		}
		mouseDown = false;
	}
}

void ChiselTool::Render(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}
