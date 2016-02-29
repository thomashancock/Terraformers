#include <SFML/Graphics.hpp>

#include <iostream>

#include "Game.hpp"

int main() {
	std::cout << "TESTING" << std::endl;

	try {
		Game game;
		game.run();
	} catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}