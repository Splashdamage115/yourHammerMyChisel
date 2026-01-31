#pragma once

#include "GameState.h"
#include "Mask.h"
#include "ChiselTool.h"

enum class Tool
{
	none, Chisel
};

class GamePlay : public GameState
{
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(sf::RenderWindow& t_window);

	static Tool heldTool;
private:
	ChiselTool m_chiselToolSlot;
	Mask m_mask;
};

