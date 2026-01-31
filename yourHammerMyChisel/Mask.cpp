#include "Mask.h"
#include "Game.h"
#include "GamePlay.h"

sf::Color MaskPixel::maskColor = sf::Color::White;

void Mask::Start(NPCController& t_npc)
{
	npc = &t_npc;
	editableMask.initMask();
}

void Mask::update()
{
	
	if (editableMask.update())
	{
		DroppedMask();
	}
}

void Mask::Render(sf::RenderWindow& t_window)
{
	editableMask.renderMask(t_window);
}

void Mask::DroppedMask()
{
	if (npc->currentEmotionNum >= savedMasks.size())
	{
		savedMasks.push_back(editableMask);
	}
	else
	{
		if (savedMasks.at(npc->currentEmotionNum) == editableMask)
		{
			DEBUG_MSG("GOOD MASK MADE");
		}
		else
		{
			// bad mask created
		}
	}

	// good mask created
	npc->recieveMask();

	editableMask = maskStruct();
	editableMask.initMask();
	
	DEBUG_MSG("GAVE MASK TO NPC");
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

bool maskStruct::update()
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
				drawMask = true;

				miniMask.setPosition(Game::mousePosition - sf::Vector2f(MINI_MASK_SIZE / 2.f, MINI_MASK_SIZE / 2.f));
				if (miniMask.getGlobalBounds().findIntersection(GamePlay::m_npcBox.getGlobalBounds()))
				{
					return true;
				}
				if (m_pixels.at(0).pixel.getPosition().x < LEFT_MIN)
				{
					sf::Vector2f move = sf::Vector2f(LEFT_MIN - (m_pixels.at(0).pixel.getPosition().x - ((MASK_PIXEL_SIZE * 3) + 30.f)),0.f);
					for (int i = 0; i < m_pixels.size(); i++)
					{
						m_pixels.at(i).setNewPositionOffset(move);
					}
				}
			}
			dragging = false;
		}
		mouseDown = false;
	}
	if (mouseDown)
	{
		if (dragging)
		{
			sf::Vector2f move = Game::mousePosition - lastMousePos;
			bool skipMove = false;
			if (Game::mousePosition.x < LEFT_MIN)
			{
				skipMove = true;
			}

			if (!skipMove)
			{
				drawMask = true;
				for (int i = 0; i < m_pixels.size(); i++)
				{
					m_pixels.at(i).setNewPositionOffset(move);
				}
			}
			else
			{
				miniMask.setPosition(Game::mousePosition - sf::Vector2f(MINI_MASK_SIZE / 2.f, MINI_MASK_SIZE / 2.f));
				drawMask = false;
			}
		}
		// handle dragging
	}

	lastMousePos = Game::mousePosition;
	return false;
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

	miniMask.setSize(sf::Vector2f(MINI_MASK_SIZE, MINI_MASK_SIZE));
	miniMask.setFillColor(sf::Color(0.f,0.f,0.f, 80.f));

}

void maskStruct::renderMask(sf::RenderWindow& t_window)
{
	if (drawMask)
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
	else
	{
		t_window.draw(miniMask);
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
