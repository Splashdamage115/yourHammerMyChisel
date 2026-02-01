#pragma once
#include "GameState.h"
#include "Game.h"
#include "GamePlay.h"

class LosingScreen : public GameState
{
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(sf::RenderWindow& t_window);
private:
	sf::Texture loseScreenTexture;
	sf::Sprite loseScreenSprite{ loseScreenTexture };

	sf::Text continueText{ Game::m_jerseyFont };
};

