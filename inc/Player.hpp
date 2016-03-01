#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window.hpp>
#include <iostream>

#include "CommandQueue.hpp"
#include "Command.hpp"
#include "Category.hpp"

class Player {
public:
	void handleEvent(
		const sf::Event& event,
		CommandQueue& commands
	);

	void handleRealtimeInput(
		CommandQueue& commands
	);
};

#endif /* PLAYER_HPP */