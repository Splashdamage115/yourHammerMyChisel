#include "NPCController.h"
#include "GamePlay.h"
#include "Game.h"

enum Moods
{
	HAPPY = 0,
	SAD = 1,
	ANGRY = 2,
	DISGUST = 3,
	FEAR = 4,
	FAITH = 5,
	DREAD = 6,
	ECCENTRIC = 7,
	FALLING = 8,
	MOODMAN = 9
};

void Npc::init(Dialogue t_lines, int emotionNum, TextureType t_tex)
{
	if (t_tex == TextureType::moodman)
	{
		standPos = -32.f;
		moodman = true;
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

	if (!moodmanEntrySoundBuffer.loadFromFile("ASSETS\\AUDIO\\moodman_entry.wav"))
	{
		std::cout << "ERROR: couldn't load moodman_entry.wav" << std::endl;
	}

	if (!clientEntrySoundBuffer.loadFromFile("ASSETS\\AUDIO\\client_entry.wav"))
	{
		std::cout << "ERROR: couldn't load client_entry.wav" << std::endl;
	}

	m_todayNpcs.clear();
	if (t_day == 0)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello.");
		newLines.dialogue.emplace_back("Good evening.");
		newLines.dialogue.emplace_back("What is 'happy?'");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::HAPPY, TextureType::moodman);

		


		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello.");
		newLines.dialogue.emplace_back("Can you make me happy?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::HAPPY, TextureType::client);

	}

	if (t_day == 1)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("Good evening.");
		newLines.dialogue.emplace_back("What is 'sad'?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::SAD, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello...");
		newLines.dialogue.emplace_back("Can you make me sad? Please?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::SAD, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello.");
		newLines.dialogue.emplace_back("Please make me happy.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::HAPPY, TextureType::client);
	}

	if (t_day == 2)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("Hello again.");
		newLines.dialogue.emplace_back("What is 'angry'?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::ANGRY, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello.");
		newLines.dialogue.emplace_back("Make me sad.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::SAD, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello.");
		newLines.dialogue.emplace_back("I want to be angry.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::ANGRY, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hi.");
		newLines.dialogue.emplace_back("Are you able to make me happy?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::HAPPY, TextureType::client);
	}

	if (t_day == 3)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("Good evening.");
		newLines.dialogue.emplace_back("What is 'disgust'?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::DISGUST, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hi.");
		newLines.dialogue.emplace_back("Make me happy.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::HAPPY, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello!");
		newLines.dialogue.emplace_back("I want to be disgusted");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::DISGUST, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Greetings.");
		newLines.dialogue.emplace_back("Make me angry. Very angry.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::ANGRY, TextureType::client);
	}

	if (t_day == 4)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("Good evening.");
		newLines.dialogue.emplace_back("What is 'fear'?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::FEAR, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("It's dark out today.");
		newLines.dialogue.emplace_back("Make me sad, please");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::SAD, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Salutations!");
		newLines.dialogue.emplace_back("Make me happy!");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::HAPPY, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("I don't like the look of you.");
		newLines.dialogue.emplace_back("Make me disgusted.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::DISGUST, TextureType::client);
	}

	if (t_day == 5)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("Your work has been acceptable thus far. Well done.");
		newLines.dialogue.emplace_back("What is 'faith'?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::FAITH, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello.");
		newLines.dialogue.emplace_back("Make me fearful.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::FEAR, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Good day.");
		newLines.dialogue.emplace_back("Give me faith.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::FAITH, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello.");
		newLines.dialogue.emplace_back("Make me happy.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::HAPPY, TextureType::client);
	}

	if (t_day == 6)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("Good evening.");
		newLines.dialogue.emplace_back("What is 'dread'?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::DREAD, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Listen to me.");
		newLines.dialogue.emplace_back("I need to be angry, now.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::ANGRY, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hi.");
		newLines.dialogue.emplace_back("Could I be sad?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::SAD, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Everything hurts.");
		newLines.dialogue.emplace_back("Make me disgusted.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::DISGUST, TextureType::client);
	}

	if (t_day == 7)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("Do you know what time it is?");
		newLines.dialogue.emplace_back("What is 'eccentric'?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::ECCENTRIC, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("HELLO");
		newLines.dialogue.emplace_back("ECCENTRIC");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::ECCENTRIC, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("...");
		newLines.dialogue.emplace_back("..dread.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::DREAD, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("i am");
		newLines.dialogue.emplace_back("happy");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::HAPPY, TextureType::client);
	}

	if (t_day == 8)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("You must be very cold.");
		newLines.dialogue.emplace_back("What is 'falling'?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::FALLING, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("I'm scared.");
		newLines.dialogue.emplace_back("...fear.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::FEAR, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("He's following me.");
		newLines.dialogue.emplace_back("Happy. I need to feel happy.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::HAPPY, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello.");
		newLines.dialogue.emplace_back("Can you give me faith?");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::FAITH, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("I need...");
		newLines.dialogue.emplace_back("Eccentricity.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::ECCENTRIC, TextureType::client);
	}

	if (t_day == 9)
	{
		// create new NPC for Today
		m_todayNpcs.emplace_back();
		Dialogue newLines;
		newLines.dialogue.emplace_back("Hello Again");
		newLines.dialogue.emplace_back("I hope that this will be the last time we meet.");
		newLines.dialogue.emplace_back("What am I? Don't disappoint me.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::MOODMAN, TextureType::moodman);




		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Him.");
		newLines.dialogue.emplace_back("Give me him.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::MOODMAN, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("I want to be him.");
		newLines.dialogue.emplace_back("Please, him.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::MOODMAN, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("I don't understand what's happening.");
		newLines.dialogue.emplace_back("Fearful. Make that.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::FEAR, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Did you see him?");
		newLines.dialogue.emplace_back("Make he him.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::MOODMAN, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Make me..");
		newLines.dialogue.emplace_back("Sad.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::SAD, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("These times are hopeless.");
		newLines.dialogue.emplace_back("Give me faith. I need it.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::FAITH, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("Hello. Hello.");
		newLines.dialogue.emplace_back("Eccentric, please.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::ECCENTRIC, TextureType::client);

		m_todayNpcs.emplace_back();
		newLines = Dialogue();
		newLines.dialogue.emplace_back("...");
		newLines.dialogue.emplace_back("The Moodman.");

		m_todayNpcs.at(m_todayNpcs.size() - 1).init(newLines, Moods::MOODMAN, TextureType::client);
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

	if (m_todayNpcs.at(m_currentnpc).moodman)
	{
		moodmanEntrySound.play();
	}
	else
	{
		clientEntrySound.play();
	}

	bufferedText.clear();
	currentText.clear();
	textPosition = 0;
}

void NPCController::badMask()
{
	Npc n;
	Dialogue d;
	d.dialogue.emplace_back("You were mistaken.");
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
