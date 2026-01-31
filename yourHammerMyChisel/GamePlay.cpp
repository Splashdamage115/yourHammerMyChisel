#include "GamePlay.h"
#include "Game.h"
#include "WinningScreen.h"

Tool GamePlay::heldTool = Tool::none;
ItemBeingHeld GamePlay::itemHeld = ItemBeingHeld::none;
bool GamePlay::pageOnTop = false;
sf::RectangleShape GamePlay::m_npcBox;
int GamePlay::currentEmotion = 0;

void GamePlay::Start()
{
	m_npcBox.setSize(sf::Vector2f(LEFT_MIN, SCREEN_HEIGHT));

	m_npcs.Start(0);
	m_page.Start();
	m_mask.Start(m_npcs);
	m_brushToolSlot.Start(Tool::Brush, sf::Vector2f(1500.f, 0.f));
	m_chiselToolSlot.Start(Tool::Chisel, sf::Vector2f(1700.f, 0.f));

	overlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	overlay.setFillColor(sf::Color::Transparent);
}

void GamePlay::Update()
{
	if (transitionNewDay)
	{
		if (delayLeft >= 0.f)
		{
			delayLeft -= Game::deltaTime;
		}
		else
		{
			opacity += Transition * Game::deltaTime;
			if (opacity >= 1.f)
			{
				opacity = 1.0f;
				Transition = Transition * -1;
				delayLeft = 2.0f;

				if (currentDay >= MAX_DAYS)
				{
					DEBUG_MSG("YOU HAVE WON THE GAME!");
					Game::getInstance().changeGameState(std::make_shared<WinningScreen>());
					return;
				}
				else
				{
					m_npcs.Start(currentDay);
				}
			}
			if (opacity <= 0.0f)
			{
				opacity = 0.0f;
				transitionNewDay = false;
			}
			overlay.setFillColor(sf::Color(0, 0, 0, 255 * opacity));
		}
	}
	if (pageOnTop)
	{
		m_page.Update();
		m_mask.update();
	}
	else
	{
		m_mask.update();
		m_page.Update();
	}
	m_npcs.Update();
	m_brushToolSlot.Update();
	m_chiselToolSlot.Update();
}

void GamePlay::Render(sf::RenderWindow& t_window)
{
	//t_window.draw(m_npcBox);
	if (pageOnTop)
	{
		m_mask.Render(t_window);
		m_page.Render(t_window);
	}
	else
	{
		m_page.Render(t_window);
		m_mask.Render(t_window);
	}
	m_brushToolSlot.Render(t_window);
	m_chiselToolSlot.Render(t_window);

	m_npcs.Render(t_window);

	if (transitionNewDay)
	{
		t_window.draw(overlay);
	}
}

void GamePlay::setNewHeldType(ItemBeingHeld t_newType)
{
	itemHeld = t_newType;
	if (itemHeld == ItemBeingHeld::Page)
	{
		pageOnTop = true;
	}
	if (itemHeld == ItemBeingHeld::Mask)
	{
		pageOnTop = false;
	}
}

void GamePlay::EndDay()
{
	if (!transitionNewDay)
	{
		currentDay++;
		Transition = 0.5f;
		delayLeft = 0.f;
		if (currentDay >= MAX_DAYS)
		{
			DEBUG_MSG("YOU HAVE WON THE GAME!");
		}
	}
	transitionNewDay = true;
}
