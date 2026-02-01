#pragma once

#include "Library.h"
#include "AnimatedSprite.h"
#include "Mask.h"

struct Dialogue
{
	std::vector<std::string> dialogue;
	int currentPos = 0;
};
struct copyMask
{
	void setPos(sf::Vector2f t_newPos);
	sf::Texture maskTex;
	std::vector<sf::Sprite> maskPixel;
};


class Npc
{
public:
	void init(Dialogue t_lines, int emotionNum, TextureType t_tex);
	Dialogue lines;
	int m_emotionNum = 0;

	std::shared_ptr<Sprite> m_body;

	float standPos = 128.f;
	copyMask m_mask;
	bool maskActive = false;

	bool moodman = false;
};



class NPCController
{
public:
	NPCController();
	void Start(int t_day);
	void Update();
	void Render(sf::RenderWindow& t_window);
	void recieveMask(bool loss, maskStruct t_mask);
	void badMask();

	int currentEmotionNum = 0;
	sf::Text renderedText;
	bool ToolsDropped = false;

	bool pickedUpMask = false;

	sf::Sprite mask{ maskT };
	sf::Sprite hammer{ hammerT };

	sf::SoundBuffer moodmanEntrySoundBuffer;
	sf::Sound moodmanEntrySound{ moodmanEntrySoundBuffer };

	sf::SoundBuffer clientEntrySoundBuffer;
	sf::Sound clientEntrySound{ clientEntrySoundBuffer };
private:
	float waitTillNextChar = TEXT_LETTER_DELAY;
	std::string currentText = "";
	std::string bufferedText = "";
	int textPosition = 0;

	std::vector<Npc> m_todayNpcs;
	int m_currentnpc = 0;

	bool writeText = false;

	bool waitingForNpc = true;

	float waitForSecondItemDrop = 0.5f;

	sf::Texture maskT;
	sf::Texture hammerT;

	sf::Texture pixelTex;

	bool itemDropped = false;
};

