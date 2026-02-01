#pragma once

#include "GameState.h"
#include "Game.h"
#include "GamePlay.h"

class WinningScreen : public GameState
{
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(sf::RenderWindow& t_window);
private:

	sf::Texture winScreenTexture;
	sf::Sprite winScreenSprite{ winScreenTexture };

};

