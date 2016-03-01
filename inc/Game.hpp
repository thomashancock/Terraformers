#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "CommandQueue.hpp"
#include "Player.hpp"

class Game {
	public:
		Game();
		void run();

	private:
		void processInputs();
		void update(
			sf::Time elapsedTime
		);
		void render();

		void updateViewPosition(
			sf::Time elapsedTime
		);

	private:
		sf::RenderWindow m_window;
		World m_world;
		Player m_player;

		bool m_isPaused;
};

#endif /* GAME_H */