#include "Game.h"
#include "GamePlay.h"
#include "MainMenu.h"

float Game::deltaTime;
sf::Font Game::m_jerseyFont;
sf::Vector2f Game::mousePosition = { 0.f,0.f };
std::shared_ptr<GameState>Game::m_gameState;

void Game::changeGameState(std::shared_ptr<GameState> t_newGameState)
{
	m_gameState = t_newGameState;

	m_gameState->Start();
}

Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{SCREEN_WIDTH, SCREEN_HEIGHT}, 32U}, "your Hammer my Chisel"},
	m_exitGame{false} //when true game will exit
{
	setupTexts(); // load font 
	changeGameState(std::make_shared<MainMenu>());
}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_exitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_exitGame = true;
	}
}

void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_exitGame = true; 
	}
}

void Game::update(sf::Time t_deltaTime)
{
	deltaTime = t_deltaTime.asSeconds();
	sf::Vector2i m = sf::Mouse::getPosition(m_window);
	mousePosition = sf::Vector2f(m.x, m.y);

	checkKeyboardState();
	if (m_exitGame)
	{
		m_window.close();
	}
	m_gameState->Update();
}

void Game::render()
{
	m_window.clear(ULTRAMARINE);

	m_gameState->Render(m_window);

	m_window.display();
}

void Game::setupTexts()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	//m_DELETEwelcomeMessage.setFont(m_jerseyFont);
	//m_DELETEwelcomeMessage.setString("SFML Game");
	//m_DELETEwelcomeMessage.setPosition(sf::Vector2f{ 205.0f, 240.0f });
	//m_DELETEwelcomeMessage.setCharacterSize(96U);
	//m_DELETEwelcomeMessage.setOutlineColor(sf::Color::Black);
	//m_DELETEwelcomeMessage.setFillColor(sf::Color::Red);
	//m_DELETEwelcomeMessage.setOutlineThickness(2.0f);

}

