#pragma once

#include "GameState.h"

class WinningScreen : public GameState
{
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(sf::RenderWindow& t_window);
private:

};

