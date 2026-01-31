#include "Book.h"
#include "GamePlay.h"
#include "Game.h"

void Book::Start()
{
	for (int x = 0; x < PAGE_SIZE_X; x++)
	{
		for (int y = 0; y < PAGE_SIZE_Y; y++)
		{
			m_book.m_pixels.emplace_back(sf::Vector2f(PAGE_PIXEL_SIZE, PAGE_PIXEL_SIZE));
			m_book.drawn.emplace_back(false);

			m_book.m_pixels.at(m_book.m_pixels.size() - 1).setFillColor(sf::Color::Transparent);
			m_book.m_pixels.at(m_book.m_pixels.size() - 1).setPosition(sf::Vector2f((PAGE_PIXEL_SIZE * x) + PAGE_START_X, (PAGE_PIXEL_SIZE * y) + PAGE_START_Y));

		}
	}

	m_book.collisionBox.setSize(sf::Vector2f(PAGE_PIXEL_SIZE * PAGE_SIZE_X, PAGE_PIXEL_SIZE * PAGE_SIZE_Y));
	m_book.collisionBox.setPosition(sf::Vector2f((PAGE_PIXEL_SIZE) + PAGE_START_X, (PAGE_PIXEL_SIZE) + PAGE_START_Y));
	m_book.collisionBox.setFillColor(sf::Color::White);

	m_book.shadow.setSize(sf::Vector2f(PAGE_PIXEL_SIZE * PAGE_SIZE_X, PAGE_PIXEL_SIZE * PAGE_SIZE_Y));
	m_book.shadow.setPosition(sf::Vector2f((PAGE_PIXEL_SIZE)+PAGE_START_X + 12.f, (PAGE_PIXEL_SIZE)+PAGE_START_Y + 8.f));
	m_book.shadow.setFillColor(sf::Color(0,0,0,80));
	

}

void Book::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (GamePlay::heldTool == Tool::none)
		{
			// if in bounds of book, drag book
			if (m_book.colliding())
			{
				dragging = (GamePlay::itemHeld != ItemBeingHeld::Mask) ? true : false;
				if (dragging)
				{
					if (!held)
					{
						held = true;
						m_book.collisionBox.move(sf::Vector2f(0.f, -10.f));
						for (int i = 0; i < m_book.m_pixels.size(); i++)
						{
							if (!m_book.drawn.at(i)) continue;

							m_book.m_pixels.at(i).move(sf::Vector2f(0.f, -10.f));
						}
						GamePlay::setNewHeldType(ItemBeingHeld::Page);
					}
				}
			}
		}
		if (GamePlay::heldTool == Tool::Brush)
		{
			if (m_book.colliding())
			{
				m_book.drawPixel();
			}
		}
		mouseDown = true;
	}
	else
	{
		if (mouseDown == true)
		{
			// mouse just released
			if (dragging)
			{
				held = false;
				m_book.collisionBox.move(sf::Vector2f(0.f, 10.f));
				for (int i = 0; i < m_book.m_pixels.size(); i++)
				{
					if (!m_book.drawn.at(i)) continue;

					m_book.m_pixels.at(i).move(sf::Vector2f(0.f, 10.f));
				}
				GamePlay::setNewHeldType(ItemBeingHeld::none);
			}

			dragging = false;
		}
		mouseDown = false;
	}
	if (dragging)
	{
		sf::Vector2f move = Game::mousePosition - m_lastMousePosition;
		if(m_book.collisionBox.getPosition().x + move.x >= LEFT_MIN)
			m_book.setNewPositionOffset(move);
	}
	m_lastMousePosition = Game::mousePosition;
}

void Book::Render(sf::RenderWindow& t_window)
{
	t_window.draw(m_book.shadow);
	t_window.draw(m_book.collisionBox);
	for (int i = 0; i < m_book.m_pixels.size(); i++)
	{
		if(m_book.drawn.at(i))
			t_window.draw(m_book.m_pixels.at(i));
	}
}

void BookPixels::setNewPositionOffset(sf::Vector2f t_newVector)
{
	for (int i = 0; i < m_pixels.size(); i++)
	{
		m_pixels.at(i).move(t_newVector);
	}
	collisionBox.move(t_newVector);
	shadow.move(t_newVector);
}

bool BookPixels::colliding()
{
	if (collisionBox.getGlobalBounds().contains(Game::mousePosition))
	{
		return true;
	}
	return false;
}

void BookPixels::drawPixel()
{
	for (int i = 0; i < m_pixels.size(); i++)
	{
		if (drawn.at(i)) continue;
		if (m_pixels.at(i).getGlobalBounds().contains(Game::mousePosition))
		{
			m_pixels.at(i).setFillColor(sf::Color::Black);
			drawn.at(i) = true;
			break;
		}
	}
}
