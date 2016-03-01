#include "Player.hpp"

// Public:
void Player::handleEvent(
	const sf::Event& event,
	CommandQueue& commands
) {
	// EXAMPLE CODE:
	// if ((event.type == sf::Event::KeyPressed) && 
	// 	(event.key.code == sf::Keyboard::P)) {
	// 	Command output;
	// 	output.category = Category::RightPaddle;
	// 	output.action = [] (SceneNode& s, sf::Time) {
	// 	std::cout << s.getPosition().x << "," << s.getPosition().y << std::endl;
	// 	};
	// 	commands.push(output);
	// }
}

void Player::handleRealtimeInput(
	CommandQueue& commands
) {
	// const float playerSpeed = 200.f;

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	// 	Command moveUp;
	// 	moveUp.category = Category::RightPaddle;
	// 	moveUp.action = derivedAction<Paddle>(
	// 		PaddleMover(-playerSpeed)
	// 	);
	// 	commands.push(moveUp);
	// }

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	// 	Command moveDown;
	// 	moveDown.category = Category::RightPaddle;
	// 	moveDown.action = derivedAction<Paddle>(
	// 		PaddleMover(playerSpeed)
	// 	);
	// 	commands.push(moveDown);
	// }
}