#include "Game.hpp"

/* Public Member Functions */
Game::Game() 
: m_window(sf::VideoMode(1280, 960), "Terraformers")
, m_world(m_window)
{
	m_window.setPosition(sf::Vector2i(50,50));
	m_window.setFramerateLimit(60);
}

void Game::run() {
	sf::Clock clock;

	while(m_window.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		
		processInputs();
		if (!m_isPaused) update(elapsedTime);
		render();
	}
}

/* Private Member Functions */
void Game::processInputs() {
	CommandQueue& commands = m_world.getCommandQueue();

	sf::Event event;
	while(m_window.pollEvent(event)) {
		// Set close when (x) is pressed
		if (sf::Event::Closed == event.type) {
			m_window.close();
		}

		// Set close on Ctrl+C
		if ((sf::Event::KeyPressed == event.type)&&
			(sf::Keyboard::C == event.key.code)&&
			(true == event.key.control)) {
			m_window.close();
		}

		// Checks for loss of focus
		if (sf::Event::GainedFocus == event.type) {
			m_isPaused = false;
		} else if (sf::Event::LostFocus == event.type) {
			m_isPaused = true;
		}
	}

	// All other inputs handled by the player class
	m_player.handleEvent(event,commands);
	m_player.handleRealtimeInput(commands);
}

void Game::update(
	sf::Time elapsedTime
	) {
	m_world.update(elapsedTime);
}

void Game::render() {
	m_window.clear(sf::Color::White);
	m_world.draw();
	
	m_window.display();
}