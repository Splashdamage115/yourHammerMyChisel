/// <summary>
/// author Pete Lowe May 2025
/// you need to change the above line or lose marks
/// Also don't have any member properties called Delete...
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the #endif at the bottom
/// </summary>
#include "Library.h"

#include "GameState.h"

const sf::Color ULTRAMARINE{ 5, 55,242,255 }; // const colour

class Game
{
public:
	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}

	// DELETE FUNCTIONS TO AVOID MORE INSTANCES
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	~Game();
	void run();



	static float deltaTime;
	static sf::Font m_jerseyFont;
	static sf::Vector2f mousePosition;

	void changeGameState(std::shared_ptr<GameState> t_newGameState);
	sf::RenderWindow m_window; // main SFML window
private:
	Game();
	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupTexts();
	

	bool m_exitGame; // control exiting game

	std::shared_ptr<GameState>m_gameState;
};

#pragma warning( pop ) 
#endif // !GAME_HPP

