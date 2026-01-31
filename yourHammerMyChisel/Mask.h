#pragma once

#include "Library.h"
#include "NPCController.h"

struct MaskPixel
{
	sf::RectangleShape pixel;
	sf::RectangleShape shadow;

	bool checkMouse();
	void setNewPositionOffset(sf::Vector2f t_newVector);

	static sf::Color maskColor;

	bool cut = false;
};

struct maskStruct
{
	maskStruct();
	bool operator==(const maskStruct& t_rhs);

	std::vector<MaskPixel> m_pixels;
	sf::Sprite miniMask;
	sf::Texture miniMaskT;

	// return true if the mask was given to the npc
	bool update();

	void initMask();
	void renderMask(sf::RenderWindow& t_window);

	bool drawMask = true;
private:
	sf::Vector2f lastMousePos = { 0.f,0.f };
	bool mouseDown = false;
	bool dragging = false;
};

class Mask
{
public:
	void Start(NPCController& t_npc);
	void update();
	void Render(sf::RenderWindow& t_window);

	void DroppedMask();
private:
	NPCController* npc;
	maskStruct editableMask;

	std::vector<maskStruct> savedMasks;
};

