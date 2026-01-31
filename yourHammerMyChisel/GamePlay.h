#pragma once

#include "GameState.h"
#include "Mask.h"
#include "ToolSelector.h"
#include "Book.h"
#include "NPCController.h"

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
	virtual void EndDay()override;

	static Tool heldTool;
	static ItemBeingHeld itemHeld;
	static sf::RectangleShape m_npcBox;
	static int currentEmotion;
private:
	ToolSelector m_chiselToolSlot;
	ToolSelector m_brushToolSlot;
	Mask m_mask;
	Book m_page;

	static bool pageOnTop;
	NPCController m_npcs;

	int currentDay = 0;


	sf::RectangleShape overlay;
	bool transitionNewDay = false;
	float opacity = 0.0f;
	float Transition = 0.5f;
	float delayLeft = 0.0f;
};

