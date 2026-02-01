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
	pixelTex.loadFromFile("./ASSETS/IMAGES/MaskPixel1.png");

	if (!maskT.loadFromFile("./ASSETS/IMAGES/stand_mask1.png"))
	{
		DEBUG_MSG("couldnt load table");
	}
	mask.setTexture(maskT);
	mask.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(maskT.getSize().x, maskT.getSize().y)));
	mask.setPosition(sf::Vector2f(888.0f, 0.0f));
	mask.setScale(sf::Vector2f(4.0f, 4.0f));


	if (!hammerT.loadFromFile("./ASSETS/IMAGES/stand_hammer.png"))
	{
		DEBUG_MSG("couldnt load table");
	}
	hammer.setTexture(hammerT);
	hammer.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(hammerT.getSize().x, hammerT.getSize().y)));
	hammer.setPosition(sf::Vector2f(888.0f, 0.0f));
	hammer.setScale(sf::Vector2f(4.0f, 4.0f));
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
				if (m_todayNpcs.at(m_currentnpc).lines.currentPos == m_todayNpcs.at(m_currentnpc).lines.dialogue.size() - 1)
				{
					ToolsDropped = true;

					mask.setPosition(sf::Vector2f(250.f, 700.f));
				}
				if (m_todayNpcs.at(m_currentnpc).lines.currentPos >= m_todayNpcs.at(m_currentnpc).lines.dialogue.size())
				{
					// end of dialogue
					waitTillNextChar = 999999999.f;

					if(currentEmotionNum == -1)
					{
						Game::m_gameState->EndDay(currentEmotionNum == -1);
					}
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



			bufferedText = m_todayNpcs.at(m_currentnpc).lines.dialogue.at(m_todayNpcs.at(m_currentnpc).lines.currentPos);
			m_todayNpcs.at(m_currentnpc).lines.currentPos++;

			waitingForNpc = false;
			waitTillNextChar = TEXT_LETTER_DELAY;

			currentEmotionNum = m_todayNpcs.at(m_currentnpc).m_emotionNum;
		}
		else if (m_currentnpc == m_todayNpcs.size() || (currentEmotionNum == -1 && !writeText))
		{
			Game::m_gameState->EndDay(currentEmotionNum == -1);
		}
		else
		{
			if (m_currentnpc > 0)
			{
				m_todayNpcs.at(m_currentnpc - 1).m_body->sprite.move(sf::Vector2f(300.f * Game::deltaTime, 0.0f));
				if (m_todayNpcs.at(m_currentnpc - 1).maskActive)
				{
					m_todayNpcs.at(m_currentnpc - 1).m_mask.setPos(sf::Vector2f(300.f * Game::deltaTime, 0.0f));
				}
			}
			if (m_currentnpc < m_todayNpcs.size())m_todayNpcs.at(m_currentnpc).m_body->sprite.move(sf::Vector2f(200.f * Game::deltaTime, 0.0f));
		}
	}

	if (ToolsDropped && currentEmotionNum != -1)
	{
		waitForSecondItemDrop -= Game::deltaTime;

		if (waitForSecondItemDrop <= 0.0f)
		{
			if(!itemDropped)
				hammer.setPosition(sf::Vector2f(450.f, 700.f));
			itemDropped = true;
		}
		if (mask.getPosition().y < ITEM_DROP_Y)
		{
			mask.move(sf::Vector2f(0.0f, 200.0f * Game::deltaTime));
		}
		if (hammer.getPosition().y < ITEM_DROP_Y)
		{
			hammer.move(sf::Vector2f(0.0f, 200.0f * Game::deltaTime));
		}
	}

	if (GamePlay::m_npcBox.getGlobalBounds().contains(Game::mousePosition))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && GamePlay::heldTool == Tool::none)
		{
			if (ToolsDropped)
			{
				// retrieve tools here
				mask.setPosition(sf::Vector2f(-2000.0f, -2000.0f));
				hammer.setPosition(sf::Vector2f(-2000.0f, -2000.0f));
				waitForSecondItemDrop = 0.5f;
				ToolsDropped = false;
				itemDropped = false;
				pickedUpMask = true;
				GamePlay::hammerGone = false;
			}
			else
			{
				writeText = true;
			}
		}
	}
}

void NPCController::Render(sf::RenderWindow& t_window)
{

	if (m_currentnpc > 0) { 
		t_window.draw(m_todayNpcs.at(m_currentnpc - 1).m_body->sprite);

		if (m_todayNpcs.at(m_currentnpc - 1).maskActive)
		{
			for (int i = 0; i < m_todayNpcs.at(m_currentnpc - 1).m_mask.maskPixel.size(); i++)
				t_window.draw(m_todayNpcs.at(m_currentnpc - 1).m_mask.maskPixel.at(i));
		}
	}
	if (m_currentnpc < m_todayNpcs.size())
	{
		if(m_todayNpcs.at(m_currentnpc).m_body != nullptr)
			try
			{
				t_window.draw(m_todayNpcs.at(m_currentnpc).m_body->sprite);
				
			}
			catch(std::exception t)
			{

			}
	}

	//if (ToolsDropped)
	//{
	//	t_window.draw(hammer);
	//	t_window.draw(mask);
	//
	//}
}

void NPCController::recieveMask(bool loss, maskStruct t_mask)
{
	//m_todayNpcs.at(m_currentnpc).m_mask = t_mask;

		for (int y = 0;y < WASK_HEIGHT; y++)
		{
			for (int x = 0; x < MASK_WIDTH; x++)
			{
			int i = (y * MASK_WIDTH) + x;
			//DEBUG_MSG(i);
			if (t_mask.m_pixels.at(i).cut) continue;

			m_todayNpcs.at(m_currentnpc).m_mask.maskPixel.emplace_back(pixelTex);

			m_todayNpcs.at(m_currentnpc).m_mask.maskPixel.at(m_todayNpcs.at(m_currentnpc).m_mask.maskPixel.size() - 1).setTexture(pixelTex);
			m_todayNpcs.at(m_currentnpc).m_mask.maskPixel.at(m_todayNpcs.at(m_currentnpc).m_mask.maskPixel.size() - 1).setPosition(
			sf::Vector2f(((MASK_PIXEL_SIZE / 4.f) * x), (((MASK_PIXEL_SIZE - 28) / 4.f) * y)) + sf::Vector2f(400.f,350.f));
			m_todayNpcs.at(m_currentnpc).m_mask.maskPixel.at(m_todayNpcs.at(m_currentnpc).m_mask.maskPixel.size() - 1).setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(pixelTex.getSize().x, pixelTex.getSize().y)));
			//m_pixels.at(m_pixels.size() - 1).pixel.setTexture(t_textureTile);
			//m_pixels.at(m_pixels.size() - 1).pixel.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(t_textureTile.getSize().x, t_textureTile.getSize().y)));
			//m_pixels.at(m_pixels.size() - 1).pixel.setPosition(sf::Vector2f(((MASK_PIXEL_SIZE + MASK_PIXEL_OFFSET) * x) + MASK_START_X, ((MASK_PIXEL_SIZE + MASK_PIXEL_OFFSET - 28) * y) + MASK_START_Y));
			//m_pixels.at(m_pixels.size() - 1).pixel.setScale(sf::Vector2f(4.0f, 4.0f));
		}
	}

	//m_todayNpcs.at(m_currentnpc).m_mask.
	m_todayNpcs.at(m_currentnpc).maskActive = true;

	m_currentnpc++;

	if (loss) badMask();

	waitingForNpc = true;
	bufferedText.clear();
	currentText.clear();
	textPosition = 0;
}

void NPCController::badMask()
{
	Npc n;
	Dialogue d;
	d.dialogue.emplace_back("THAT WAS A WRONG MASK!!!!!");
	n.init(d, -1, TextureType::moodman);
	if (m_currentnpc >= m_todayNpcs.size())
	{
		m_todayNpcs.emplace_back(n);
	}
	else
	{
		m_todayNpcs.at(m_currentnpc) = n;

	}
}

void copyMask::setPos(sf::Vector2f t_newPos)
{
	for (int i = 0; i < maskPixel.size(); i++)
	{
		maskPixel.at(i).setPosition(maskPixel.at(i).getPosition() + t_newPos);
	}
}
