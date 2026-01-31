#pragma once

#include "GameState.h"

class MainMenu : public GameState
{
public:
	void Start();
	void Update();
	void Render(sf::RenderWindow & t_window);
	bool startButtonColliding();
private:

	sf::RectangleShape startButtonRect;

	sf::Texture startButtonTexture;
	sf::Sprite startButtonSprite{ startButtonTexture };

	bool startButtonHovering = false;
	bool startButtonPressed = false;
	
};

