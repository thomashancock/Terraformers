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

		// Catch resize events
		if (sf::Event::Resized == event.type) {
			sf::FloatRect visibleArea(0,0,event.size.width,event.size.height);
			m_window.setView(sf::View(visibleArea));
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

	// View Scrolling
	updateViewPosition(elapsedTime);
}

void Game::render() {
	m_window.clear(sf::Color::White);
	m_world.draw();
	
	m_window.display();
}

void Game::updateViewPosition(
	sf::Time elapsedTime
	) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	sf::Vector2u windowSize = m_window.getSize();

	// Ensure mouse is inside window
	if ((mousePos.x > 0)&&
			(mousePos.x < (int) windowSize.x)&&
			(mousePos.y > 0)&&
			(mousePos.y < (int) windowSize.y)) {
		sf::Vector2<int> scrollSpeed(0,0);

		// Set y scroll speed based on mouse position
		if (mousePos.y < (windowSize.y/10.0)) {
			scrollSpeed.y = -100;
		} else if (mousePos.y > (windowSize.y - (windowSize.y/10.0))) {
			scrollSpeed.y = 100;
		}

		// Set x scroll speed based on mouse position
		if (mousePos.x < (windowSize.x/10.0)) {
			scrollSpeed.x = -100;
		} else if (mousePos.x > (windowSize.x - (windowSize.x/10.0))) {
			scrollSpeed.x = 100;
		}

		// Update view using scroll speeds determined
		sf::View view = m_window.getView();
		view.move(scrollSpeed.x*elapsedTime.asSeconds(),scrollSpeed.y*elapsedTime.asSeconds());
		m_window.setView(view);
	}
}