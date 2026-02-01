#pragma once

#include "Library.h"

class NPCController;

struct MaskPixel
{
	sf::Sprite pixel{ maskTile };
	sf::RectangleShape shadow;
	sf::Texture maskTile;

	bool checkMouse();
	void setNewPositionOffset(sf::Vector2f t_newVector);

	static sf::Color maskColor;

	bool cut = false;
};

struct maskStruct
{
	maskStruct();
	maskStruct(sf::Texture& t_texture, sf::Texture& t_textureTile);
	bool operator==(const maskStruct& t_rhs);

	std::vector<MaskPixel> m_pixels;
	sf::Sprite miniMask;

	// return true if the mask was given to the npc
	bool update();

	void setMaskPos(sf::Vector2f t_newPos);

	void initMask(sf::Texture& t_textureTile);
	void renderMask(sf::RenderWindow& t_window);

	void setNewSize(sf::Vector2f t_newScale);

	bool drawMask = true;
	sf::Texture maskTile;

	float mouseHeldTime = 0.0f;
private:
	sf::Vector2f lastMousePos = { 0.f,0.f };
	bool mouseDown = false;
	bool dragging = false;
	float moveDownTimeLeft = 1.0f;
};

class Mask
{
public:
	Mask();
	void Start(NPCController& t_npc);
	void update();
	void Render(sf::RenderWindow& t_window);

	void DroppedMask();

	void SpawnMask();
private:
	NPCController* npc;
	maskStruct editableMask;

	std::vector<maskStruct> savedMasks;
	sf::Texture miniMaskT;
	sf::Texture maskTile;

	bool noMask = true;
};

