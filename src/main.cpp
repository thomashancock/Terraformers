// STD
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>

// LOCAL
#include "Debug.hpp"
#include "Game.hpp"

int main() {
	STD_LOG("Running Debug Build");

	try {
		Game game;
		game.run();
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
