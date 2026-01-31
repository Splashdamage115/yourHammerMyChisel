#include "GamePlay.h"

Tool GamePlay::heldTool = Tool::none;

void GamePlay::Start()
{
	m_mask.Start();
	m_brushToolSlot.Start(Tool::Brush, sf::Vector2f(1500.f, 0.f));
	m_chiselToolSlot.Start(Tool::Chisel, sf::Vector2f(1700.f, 0.f));
}

void GamePlay::Update()
{
	m_mask.update();
	m_brushToolSlot.Update();
	m_chiselToolSlot.Update();
}

void GamePlay::Render(sf::RenderWindow& t_window)
{
	m_mask.Render(t_window);
	m_brushToolSlot.Render(t_window);
	m_chiselToolSlot.Render(t_window);
}
