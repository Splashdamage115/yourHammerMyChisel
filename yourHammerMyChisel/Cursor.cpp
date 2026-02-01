#include "Cursor.h"
#include "Game.h"
#include "GamePlay.h"

void Cursor::Start()
{
	if (!cursorTexture.loadFromFile("ASSETS\\IMAGES\\cursors.png"))
	{
		std::cout << "ERROR: Couldn't load 'cursors.png'" << std::endl;
	}
	cursorSprite.setTexture(cursorTexture);
	cursorSprite.setScale(sf::Vector2f{ 4.0f, 4.0f });
	cursorSprite.setOrigin(sf::Vector2f{ 0.0f, 21.0f });
	cursorSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0, 0}, sf::Vector2i{22, 21} });
}

void Cursor::Update()
{
	if (GamePlay::heldTool == Tool::Chisel)
	{
		cursorSprite.setTextureRect(sf::IntRect{ sf::Vector2i{22, 0}, sf::Vector2i{22, 21} });
	}
	else if (GamePlay::heldTool == Tool::Brush)
	{
		cursorSprite.setTextureRect(sf::IntRect{ sf::Vector2i{44, 0}, sf::Vector2i{22, 21} });
	}
	else if (GamePlay::heldTool == Tool::none)
	{
		cursorSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0, 0}, sf::Vector2i{22, 21} });
	}

	cursorSprite.setPosition(Game::mousePosition);
}

void Cursor::Render(sf::RenderWindow & t_window)
{
	t_window.draw(cursorSprite);
}
