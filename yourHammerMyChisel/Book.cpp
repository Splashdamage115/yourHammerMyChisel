#include "Book.h"
#include "GamePlay.h"
#include "Game.h"

void Book::Start()
{
}

void Book::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (GamePlay::heldTool == Tool::none)
		{
			// if in bounds of book, drag book
		}
		if (GamePlay::heldTool == Tool::Brush)
		{
			// if in bounds of book, draw on book
		}
		mouseDown = true;
	}
	else
	{
		if (mouseDown == true)
		{
			// mouse just released
			//if (body.getGlobalBounds().contains(Game::mousePosition))
			//{
			//	
			//}
		}
		mouseDown = false;
	}
}

void Book::Render(sf::RenderWindow& t_window)
{
}
