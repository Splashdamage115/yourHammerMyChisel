#include "GamePlay.h"

Tool GamePlay::heldTool = Tool::none;

void GamePlay::Start()
{
	m_mask.Start();
	m_chiselToolSlot.Start();
}

void GamePlay::Update()
{
	m_mask.update();
	m_chiselToolSlot.Update();
}

void GamePlay::Render(sf::RenderWindow& t_window)
{
	m_mask.Render(t_window);
	m_chiselToolSlot.Render(t_window);
}
