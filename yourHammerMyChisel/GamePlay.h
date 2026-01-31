#pragma once

#include "GameState.h"
#include "Mask.h"
#include "ToolSelector.h"

enum class Tool
{
	none, Chisel, Brush
};

class GamePlay : public GameState
{
public:
	GamePlay() {}
	virtual void Start();
	virtual void Update();
	virtual void Render(sf::RenderWindow& t_window);

	static Tool heldTool;
private:
	ToolSelector m_chiselToolSlot;
	ToolSelector m_brushToolSlot;
	Mask m_mask;
};

