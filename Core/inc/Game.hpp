#ifndef GAME_H
#define GAME_H

// SFML
#include <SFML/Graphics.hpp>

// LOCAL
#include "World.hpp"
#include "Player.hpp"

//! The Game class
/*!
	Class which manages and runs the game
*/
class Game {
public:
	//! Constructor
	Game();

	//! Run function which runs game
	void run();

private:
	//! Processes player input
	void processInputs();

	//! Updated the game state
	void update(
		sf::Time elapsedTime //!< Elpased time since previous update
	);

	//! Renders the game
	void render();

private:
	sf::RenderWindow m_window; //!< The Game Window
	World m_world; //!< The game world class
	Player m_player; //!< The player class

	bool m_isPaused = false; //!< Is the game paused?
};

#endif /* GAME_H */
