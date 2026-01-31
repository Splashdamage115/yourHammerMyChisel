#pragma once

#include "Library.h"
#include "AnimatedSprite.h"

struct Dialogue
{
	std::vector<std::string> dialogue;
	int currentPos = 0;
};

class Npc
{
public:
	void init(Dialogue t_lines, int emotionNum, TextureType t_tex);
	Dialogue lines;
	int m_emotionNum = 0;

	std::shared_ptr<Sprite> m_body;

	float standPos = 128.f;

};

class NPCController
{
public:
	NPCController();
	void Start(int t_day);
	void Update();
	void Render(sf::RenderWindow& t_window);
	void recieveMask();

	int currentEmotionNum = 0;
	sf::Text renderedText;
private:
	float waitTillNextChar = TEXT_LETTER_DELAY;
	std::string currentText = "";
	std::string bufferedText = "";
	int textPosition = 0;

	std::vector<Npc> m_todayNpcs;
	int m_currentnpc = 0;

	bool writeText = false;

	bool waitingForNpc = true;
};

