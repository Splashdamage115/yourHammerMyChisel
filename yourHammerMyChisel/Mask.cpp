#include "Mask.h"
#include "Game.h"
#include "GamePlay.h"

sf::Color MaskPixel::maskColor = sf::Color::White;

void Mask::Start()
{
	editableMask.initMask();
}

void Mask::update()
{
	editableMask.update();
}

void Mask::Render(sf::RenderWindow& t_window)
{
	editableMask.renderMask(t_window);
}

bool maskStruct::operator==(const maskStruct& t_rhs)
{
	int incorrectPixels = 0;
	for (int i = 0; i < m_pixels.size(); i++)
	{
		if (m_pixels.at(i).cut != t_rhs.m_pixels.at(i).cut)incorrectPixels++;
	}
	if (incorrectPixels >= (m_pixels.size() * MAX_WRONG_PERCENT)) return false;
	return true;
}

void maskStruct::update()
{
	bool mouseInside = false;
	for (int i = 0; i < m_pixels.size(); i++)
	{
		mouseInside = m_pixels.at(i).checkMouse();
		if (mouseInside && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) break;
	}

	if ((mouseInside && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && GamePlay::heldTool == Tool::none))
	{
		if (!mouseDown)
		{
			dragging = (GamePlay::itemHeld != ItemBeingHeld::Page) ? true : false;
			if (dragging) {
				GamePlay::setNewHeldType(ItemBeingHeld::Mask);
				for (int i = 0; i < m_pixels.size(); i++)
				{
					//m_pixels.at(i).pixel.setSize(sf::Vector2f(MASK_PIXEL_SIZE + 4.f, MASK_PIXEL_SIZE + 4.f));
					m_pixels.at(i).pixel.move(sf::Vector2f(0.f, -15.0f));
				}
			}
		}
		mouseDown = true;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (mouseDown)
		{

			// just dropped
			if (dragging)
			{
				GamePlay::setNewHeldType(ItemBeingHeld::none);
				for (int i = 0; i < m_pixels.size(); i++)
				{
					//m_pixels.at(i).pixel.setSize(sf::Vector2f(MASK_PIXEL_SIZE, MASK_PIXEL_SIZE));

					m_pixels.at(i).pixel.move(sf::Vector2f(0.f, 15.0f));
				}
				DEBUG_MSG("dropped mask");
			}
			dragging = false;
		}
		mouseDown = false;
	}
	if (mouseDown)
	{
		if (dragging)
		{
			for (int i = 0; i < m_pixels.size(); i++)
			{
				m_pixels.at(i).setNewPositionOffset(Game::mousePosition - lastMousePos);
			}
		}
		// handle dragging
	}

	lastMousePos = Game::mousePosition;
}

void maskStruct::initMask()
{
	std::vector<sf::Vector2i> skipNums =
	{
		{0,0}, {0,1}, {1,0}, {MASK_WIDTH - 1 , 0}, {MASK_WIDTH - 1 , 1}, {MASK_WIDTH - 2 , 0},
		{0,WASK_HEIGHT - 1}, {0,WASK_HEIGHT - 2}, {1,WASK_HEIGHT - 1}, {MASK_WIDTH - 1,WASK_HEIGHT - 1}, {MASK_WIDTH - 1,WASK_HEIGHT - 2}, {MASK_WIDTH - 2,WASK_HEIGHT - 1}
	};

	for (int y = 0; y < WASK_HEIGHT; y++)
	{
		for (int x = 0; x < MASK_WIDTH; x++)
		{
			bool found = false;
			for (int s = 0; s < skipNums.size(); s++)
				if (x == skipNums.at(s).x && y == skipNums.at(s).y)
				{
					found = true;
					break;
				}
			if (found) continue;

			m_pixels.emplace_back();
			m_pixels.at(m_pixels.size() - 1).pixel.setSize(sf::Vector2f(MASK_PIXEL_SIZE, MASK_PIXEL_SIZE));
			m_pixels.at(m_pixels.size() - 1).pixel.setFillColor(MaskPixel::maskColor);
			m_pixels.at(m_pixels.size() - 1).pixel.setPosition(sf::Vector2f(((MASK_PIXEL_SIZE + MASK_PIXEL_OFFSET) * x) + MASK_START_X, ((MASK_PIXEL_SIZE + MASK_PIXEL_OFFSET) * y) + MASK_START_Y));
			m_pixels.at(m_pixels.size() - 1).pixel.setOutlineColor(sf::Color(0,0,0,255));
			m_pixels.at(m_pixels.size() - 1).pixel.setOutlineThickness(1u);

			m_pixels.at(m_pixels.size() - 1).shadow.setSize(sf::Vector2f(MASK_PIXEL_SIZE + MASK_PIXEL_OFFSET, MASK_PIXEL_SIZE + MASK_PIXEL_OFFSET));
			m_pixels.at(m_pixels.size() - 1).shadow.setFillColor(sf::Color(0, 0, 0, 80));
			m_pixels.at(m_pixels.size() - 1).shadow.setPosition(sf::Vector2f(((MASK_PIXEL_SIZE + MASK_PIXEL_OFFSET) * x) + MASK_START_X + MASK_SHADOW_OFFSET_X, ((MASK_PIXEL_SIZE + MASK_PIXEL_OFFSET) * y) + MASK_START_Y + MASK_SHADOW_OFFSET_Y));

		}
	}
}

void maskStruct::renderMask(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_pixels.size(); i++)
	{
		if (m_pixels.at(i).cut) continue;
		t_window.draw(m_pixels.at(i).shadow);
	}
	for (int i = 0; i < m_pixels.size(); i++)
	{
		if (m_pixels.at(i).cut) continue;
		t_window.draw(m_pixels.at(i).pixel);
	}
}

bool MaskPixel::checkMouse()
{
	if (pixel.getGlobalBounds().contains(Game::mousePosition))
	{
		if (GamePlay::heldTool == Tool::Chisel)
		{
			pixel.setFillColor(sf::Color(255, 255, 255, 125));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				cut = true;
			}
		}
		return true;
	}
	else
	{
		pixel.setFillColor(maskColor);
		return false;
	}
}

void MaskPixel::setNewPositionOffset(sf::Vector2f t_newVector)
{
	pixel.move(t_newVector);
	shadow.move(t_newVector);
}
