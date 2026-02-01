#include "MainMenu.h"
#include "Game.h"
#include "GamePlay.h"

void MainMenu::Start()
{
	// readying the start button RECT
	startButtonRect.setSize(sf::Vector2f{ 584.0f, 228.0f});
	startButtonRect.setPosition(sf::Vector2f{ 1200.0f, 1000.0f });
	startButtonRect.setFillColor(sf::Color{ 0,255,0 });

	// readying the start button SPRITE
	if (!startButtonTexture.loadFromFile("ASSETS\\IMAGES\\startbutton.png"))
	{
		std::cout << "ERROR: Can't load 'startbutton.png" << std::endl;
	}
	startButtonSprite.setTexture(startButtonTexture);
	startButtonSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0,0}, sf::Vector2i{146,57} });
	startButtonSprite.setScale(sf::Vector2f{ 4.0f,4.0f });
	startButtonSprite.setPosition(sf::Vector2f{ 1200.0f, 1000.0f });

	if (!tableTexture.loadFromFile("./ASSETS/IMAGES/table.png"))
	{
		std::cout << "couldnt load table" << std::endl;
	}
	tableSprite.setTexture(tableTexture);
	tableSprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(tableTexture.getSize().x, tableTexture.getSize().y)));
	tableSprite.setPosition(sf::Vector2f(888.0f, 0.0f));
	tableSprite.setScale(sf::Vector2f(4.0f, 4.0f));


	if (!standTexture.loadFromFile("./ASSETS/IMAGES/stand.png"))
	{
		std::cout << "couldnt load stand" << std::endl;
	}
	standSprite.setTexture(standTexture);
	standSprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(standTexture.getSize().x, standTexture.getSize().y)));
	standSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	standSprite.setScale(sf::Vector2f(4.0f, 4.0f));

}

void MainMenu::Update()
{
	if (startButtonRect.getGlobalBounds().contains(Game::mousePosition))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			startButtonPressed = true;
		}
		else if (startButtonPressed) // start button was pressed, left click is no longer active, means click was released
		{
			Game::getInstance().changeGameState(std::make_shared<GamePlay>());
		}

		startButtonHovering = true;
	}
	else
	{
		startButtonHovering = false;
		startButtonPressed = false;
	}

	// visuals

	if (startButtonHovering)
	{
		startButtonSprite.setColor(sf::Color{ 225,225,225 });
	}
	else
	{
		startButtonSprite.setColor(sf::Color{ 255,255,255 });
	}

	if (startButtonPressed)
	{
		startButtonSprite.setTextureRect(sf::IntRect{ sf::Vector2i{146,0}, sf::Vector2i{146,57} });
	}
	else {
		startButtonSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0,0}, sf::Vector2i{146,57} });
	}
}

void MainMenu::Render(sf::RenderWindow& t_window)
{
	t_window.clear(sf::Color::Black);

	t_window.draw(standSprite);
	t_window.draw(tableSprite);
	t_window.draw(startButtonSprite);
}

bool MainMenu::startButtonColliding()
{
	return false;
}
