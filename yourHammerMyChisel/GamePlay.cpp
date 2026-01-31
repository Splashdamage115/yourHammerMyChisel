#include "GamePlay.h"

Tool GamePlay::heldTool = Tool::none;
ItemBeingHeld GamePlay::itemHeld = ItemBeingHeld::none;
bool GamePlay::pageOnTop = false;

void GamePlay::Start()
{
	m_page.Start();
	m_mask.Start();
	m_brushToolSlot.Start(Tool::Brush, sf::Vector2f(1500.f, 0.f));
	m_chiselToolSlot.Start(Tool::Chisel, sf::Vector2f(1700.f, 0.f));
}

void GamePlay::Update()
{
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
	m_brushToolSlot.Update();
	m_chiselToolSlot.Update();
}

void GamePlay::Render(sf::RenderWindow& t_window)
{
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
