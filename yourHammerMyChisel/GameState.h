#pragma once
#include "Library.h"
class GameState
{
public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow& t_window) = 0;
	virtual void EndDay(bool badEnd) {}
private:

};

