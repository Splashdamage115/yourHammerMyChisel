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
}
