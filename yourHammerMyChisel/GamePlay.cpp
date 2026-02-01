#include "GamePlay.h"
#include "Game.h"
#include "WinningScreen.h"
#include "LosingScreen.h"

Tool GamePlay::heldTool = Tool::none;
ItemBeingHeld GamePlay::itemHeld = ItemBeingHeld::none;
bool GamePlay::pageOnTop = false;
sf::RectangleShape GamePlay::m_npcBox;
int GamePlay::currentEmotion = 0;
AnimatedSprite GamePlay::anims;
bool GamePlay::hammerGone = true;

GamePlay::GamePlay() : tableSprite(tableTexture), standSprite(standTexture)
{
}

void GamePlay::Start()
{
	anims.Start();
	if (!tableTexture.loadFromFile("./ASSETS/IMAGES/table.png"))
	{
		DEBUG_MSG("couldnt load table");
	}
	tableSprite.setTexture(tableTexture);
	tableSprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(tableTexture.getSize().x, tableTexture.getSize().y)));
	tableSprite.setPosition(sf::Vector2f(888.0f, 0.0f));
	tableSprite.setScale(sf::Vector2f(4.0f, 4.0f));


	if (!standTexture.loadFromFile("./ASSETS/IMAGES/stand.png"))
	{
		DEBUG_MSG("couldnt load table");
	}
	standSprite.setTexture(standTexture);
	standSprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(standTexture.getSize().x, standTexture.getSize().y)));
	standSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	standSprite.setScale(sf::Vector2f(4.0f, 4.0f));

	//if (!bgTexture.loadFromFile("./ASSETS/IMAGES/bg.png"))
	//{
	//	DEBUG_MSG("couldnt load table");
	//}
	//bgSprite.setTexture(bgTexture);

	m_bg = anims.getSprite(TextureType::bg);
	m_bg->sprite.setPosition(sf::Vector2f(132.0f, 128.0f));



	m_npcBox.setSize(sf::Vector2f(LEFT_MIN, SCREEN_HEIGHT));

	m_npcs.Start(0);
	m_page.Start();
	m_mask.Start(m_npcs);
	m_brushToolSlot.Start(Tool::Brush, sf::Vector2f(1240.f, 70.f));
	m_chiselToolSlot.Start(Tool::Chisel, sf::Vector2f(1550.f, 70.f));

	overlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	overlay.setFillColor(sf::Color::Transparent);
	cursors.Start();
}

void GamePlay::Update()
{
	anims.update();
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
				else if (lost)
				{
					DEBUG_MSG("YOU HAVE LOST THE GAME!");
					Game::getInstance().changeGameState(std::make_shared<LosingScreen>());
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
			overlay.setFillColor(sf::Color(overlay.getFillColor().r, 0, 0, 255 * opacity));
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
	if(!hammerGone)
		m_chiselToolSlot.Update();

	cursors.Update();

}

void GamePlay::Render(sf::RenderWindow& t_window)
{
	if (mouseVisible)
	{
		t_window.setMouseCursorVisible(false);
		mouseVisible = false;
	}

	t_window.draw(m_bg->sprite);
	m_npcs.Render(t_window);
	t_window.draw(standSprite);
	if (m_npcs.ToolsDropped)
	{
		t_window.draw(m_npcs.hammer);

		t_window.draw(m_npcs.mask);
	}
	t_window.draw(tableSprite);

	m_brushToolSlot.Render(t_window);
	if (!hammerGone)
		m_chiselToolSlot.Render(t_window);

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



	if (transitionNewDay)
	{
		t_window.draw(overlay);
	}
	t_window.draw(m_npcs.renderedText);
	cursors.Render(t_window);

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

void GamePlay::EndDay(bool badEnd)
{
	if (badEnd)
	{
		Transition = 0.5f;
		delayLeft = 0.f;

		overlay.setFillColor(sf::Color(255, 0, 0, 0));

		DEBUG_MSG("YOU HAVE LOST THE GAME!");

		lost = true;
	}
	else if (!transitionNewDay)
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
