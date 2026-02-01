#include "WinningScreen.h"

void WinningScreen::Start()
{
	if (!winScreenTexture.loadFromFile("ASSETS\\IMAGES\\winscreen.png"))
	{
		std::cout << "ERROR: Couldn't load 'winscreen.png'" << std::endl;
	}
	winScreenSprite.setTexture(winScreenTexture);
	winScreenSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0,0}, sf::Vector2i{516,384} });
	winScreenSprite.setScale(sf::Vector2f{ 4.0f, 4.0f });

	continueText.setString("PRESS ENTER TO CONTINUE...");
	continueText.setFillColor(sf::Color{ 255 });
	continueText.setOutlineColor(sf::Color{ 0 });
	continueText.setPosition(sf::Vector2f{ 100,100 });
	continueText.setCharacterSize(32);
}

void WinningScreen::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		Game::getInstance().changeGameState(std::make_shared<GamePlay>());
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		mouseDown = true;
	}
	if (mouseDown && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Game::getInstance().changeGameState(std::make_shared<GamePlay>());
		return;
	}
}

void WinningScreen::Render(sf::RenderWindow& t_window)
{
	t_window.draw(winScreenSprite);
	t_window.draw(continueText);
}
