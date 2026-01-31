#include "NPCController.h"
#include "GamePlay.h"
#include "Game.h"

void Npc::init(Dialogue t_lines, int emotionNum, TextureType t_tex)
{
	if (t_tex == TextureType::moodman)
	{
		standPos = -32.f;
	}
	else
	{
		standPos = STAND_X;
	}

	m_body = GamePlay::anims.getSprite(t_tex);
	//m_body.setSize(sf::Vector2f(120.f, 120.f));
	//m_body.setFillColor(sf::Color::White);
	m_body->sprite.setPosition(sf::Vector2f(-1000.f, 128.f));

	lines = t_lines;
	m_emotionNum = emotionNum;
}

NPCController::NPCController() : renderedText(Game::m_jerseyFont)
{
}

void NPCController::Start(int t_day)
{
	renderedText.setString("");
	renderedText.setFillColor(sf::Color::White);
	renderedText.setCharacterSize(32u);
	renderedText.setPosition(sf::Vector2f(40.f, 100.f));

	m_todayNpcs.clear();
	if (t_day == 0)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello");
		newLines.dialogue.emplace_back("Welcome to the game");
		newLines.dialogue.emplace_back("Make me Happy");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, 0, TextureType::moodman);

		


		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Waddup");
		newLines.dialogue.emplace_back("Make me Happy I suppose");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, 0, TextureType::client);

	}

	if (t_day == 1)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("Im back");
		newLines.dialogue.emplace_back("Make me Sad");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, 1, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Waddup");
		newLines.dialogue.emplace_back("Make me Sad I suppose");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, 1, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Waddup");
		newLines.dialogue.emplace_back("Make me Happy I suppose");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, 0, TextureType::client);
	}
	m_currentnpc = 0;
	bufferedText = m_todayNpcs.at(m_currentnpc).lines.dialogue.at(m_todayNpcs.at(m_currentnpc).lines.currentPos++);
}

void NPCController::Update()
{
	if (writeText && !waitingForNpc)
	{
		waitTillNextChar -= Game::deltaTime;

		if (waitTillNextChar <= 0.f)
		{
			waitTillNextChar = TEXT_LETTER_DELAY;

			currentText += bufferedText.at(textPosition);
			renderedText.setString(currentText);
			textPosition++;

			if (textPosition >= bufferedText.size())
			{
				if (m_todayNpcs.at(m_currentnpc).lines.currentPos >= m_todayNpcs.at(m_currentnpc).lines.dialogue.size())
				{
					// end of dialogue
					waitTillNextChar = 999999999.f;
				}
				else
				{
					bufferedText = m_todayNpcs.at(m_currentnpc).lines.dialogue.at(m_todayNpcs.at(m_currentnpc).lines.currentPos++);
				}
				textPosition = 0;
				currentText.clear();
				writeText = false;
			}
		}
	}
	else if (waitingForNpc)
	{
		if (m_currentnpc < m_todayNpcs.size() && m_todayNpcs.at(m_currentnpc).m_body->sprite.getPosition().x >= m_todayNpcs.at(m_currentnpc).standPos)
		{
			// ARRIVED AT STAND

			bufferedText = m_todayNpcs.at(m_currentnpc).lines.dialogue.at(m_todayNpcs.at(m_currentnpc).lines.currentPos++);


			waitingForNpc = false;
			waitTillNextChar = TEXT_LETTER_DELAY;

			currentEmotionNum = m_todayNpcs.at(m_currentnpc).m_emotionNum;
		}
		else if (m_currentnpc == m_todayNpcs.size())
		{
			Game::m_gameState->EndDay();
		}
		else
		{
			if (m_currentnpc > 0)m_todayNpcs.at(m_currentnpc - 1).m_body->sprite.move(sf::Vector2f(300.f * Game::deltaTime, 0.0f));
			if (m_currentnpc < m_todayNpcs.size())m_todayNpcs.at(m_currentnpc).m_body->sprite.move(sf::Vector2f(200.f * Game::deltaTime, 0.0f));
		}
	}

	if (GamePlay::m_npcBox.getGlobalBounds().contains(Game::mousePosition))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && GamePlay::heldTool == Tool::none)
		{
			writeText = true;
		}
	}
}

void NPCController::Render(sf::RenderWindow& t_window)
{

	if(m_currentnpc > 0) t_window.draw(m_todayNpcs.at(m_currentnpc - 1).m_body->sprite);
	if (m_currentnpc < m_todayNpcs.size())t_window.draw(m_todayNpcs.at(m_currentnpc).m_body->sprite);

}

void NPCController::recieveMask()
{
	m_currentnpc++;

	waitingForNpc = true;

}