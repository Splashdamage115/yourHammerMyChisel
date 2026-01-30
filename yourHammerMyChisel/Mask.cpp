#include "Mask.h"

void Mask::Start()
{
	editableMask.initMask();
}

void Mask::update()
{
}

void Mask::Render(sf::RenderWindow& t_window)
{
	editableMask.renderMask(t_window);
}

void mask::initMask()
{
	for (int x = 0; x < MASK_WIDTH; x++)
	{
		for (int y = 0; y < WASK_HEIGHT; y++)
		{
			m_pixels.emplace_back();
			m_pixels.at(m_pixels.size() - 1).pixel.setSize(sf::Vector2f(10.f, 10.f));
			m_pixels.at(m_pixels.size() - 1).pixel.setFillColor(sf::Color::White);
			m_pixels.at(m_pixels.size() - 1).pixel.setPosition(sf::Vector2f(((10.f + 1.f) * x) + 0.f, ((10.f + 1.f) * y) + 0.f));
		}
	}
}

void mask::renderMask(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_pixels.size(); i++)
	{
		t_window.draw(m_pixels.at(i).pixel);
	}
}
