#pragma once

#include "GameState.h"
#include "Mask.h"
#include "ToolSelector.h"
#include "Book.h"

enum class Tool
{
	none, Chisel, Brush
};

enum class ItemBeingHeld
{
	none, Page, Mask
};

class GamePlay : public GameState
{
public:
	GamePlay() {}
	virtual void Start();
	virtual void Update();
	virtual void Render(sf::RenderWindow& t_window);
	static void setNewHeldType(ItemBeingHeld t_newType);

	static Tool heldTool;
	static ItemBeingHeld itemHeld;
private:
	ToolSelector m_chiselToolSlot;
	ToolSelector m_brushToolSlot;
	Mask m_mask;
	Book m_page;

	static bool pageOnTop;
};

