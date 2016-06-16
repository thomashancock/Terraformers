#include "Player.hpp"

// Public:
void Player::handleEvent(
	const sf::Event& event,
	CommandQueue& commands
) {
	// if (sf::Event::MouseButtonPressed == event.type) {
	// 		if (sf::Mouse::Left == event.mouseButton.button) {
	// 			Command keyPress(Input::Type::LeftMouse);
	// 			commands.push(keyPress);
	// 		}
	//
	// 		if (sf::Mouse::Right == event.mouseButton.button) {
	// 			Command keyPress(Input::Type::RightMouse);
	// 			commands.push(keyPress);
	// 		}
	// }
	//
	// if (sf::Event::KeyPressed == event.type) {
	// 	if (sf::Keyboard::Space == event.key.code) {
	// 		STD_LOG("Pushing Spacebar command to Command Queue");
	// 		Command keyPress(Input::Type::Spacebar);
	// 		commands.push(keyPress);
	// 	}
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
