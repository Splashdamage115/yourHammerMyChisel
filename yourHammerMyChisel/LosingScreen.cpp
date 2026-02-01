#include "LosingScreen.h"

void LosingScreen::Start()
{
	if (!loseScreenTexture.loadFromFile("ASSETS\\IMAGES\\losescreen.png"))
	{
		std::cout << "ERROR: Couldn't load 'losescreen.png'" << std::endl;
	}
	loseScreenSprite.setTexture(loseScreenTexture);
	loseScreenSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0,0}, sf::Vector2i{516,384} });
	loseScreenSprite.setScale(sf::Vector2f{ 4.0f, 4.0f });

	continueText.setString("PRESS ENTER TO CONTINUE...");
	continueText.setFillColor(sf::Color{ 255,255,255 });
	continueText.setOutlineColor(sf::Color{ 0,0,0 });
	continueText.setPosition(sf::Vector2f{ 100,100 });
	continueText.setCharacterSize(32);
}

void LosingScreen::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		Game::getInstance().changeGameState(std::make_shared<GamePlay>());
	}
}

void LosingScreen::Render(sf::RenderWindow& t_window)
{
	t_window.draw(loseScreenSprite);
	t_window.draw(continueText);
}
