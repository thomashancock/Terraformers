#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window.hpp>
#include <iostream>

#include "CommandQueue.hpp"
#include "Command.hpp"
#include "Category.hpp"
#include "Paddle.hpp"

struct PaddleMover {
	PaddleMover(
		float vy
	) : velocity(0, vy)
	{
	}

	void operator() (Paddle& paddle, sf::Time) const
	{
		paddle.setVelocity(velocity);
	}

	sf::Vector2f velocity;
};

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