#pragma once

#include "Library.h"

struct Dialogue
{
	std::vector<std::string> dialogue;
	int currentPos = 0;
};

class Npc
{
public:
	void init(Dialogue t_lines, int emotionNum);
	Dialogue lines;
	int m_emotionNum = 0;

	sf::RectangleShape m_body;
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
private:
	sf::Text renderedText;
	float waitTillNextChar = TEXT_LETTER_DELAY;
	std::string currentText = "";
	std::string bufferedText = "";
	int textPosition = 0;

	std::vector<Npc> m_todayNpcs;
	int m_currentnpc = 0;

	bool writeText = false;

	bool waitingForNpc = true;
};

