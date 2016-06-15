#include <SFML/Graphics.hpp>

#include <iostream>

#include "Debug.hpp"
#include "Game.hpp"

int main() {
	STD_LOG("Running Debug Build");

	try {
		Game game;
		game.run();
	} catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}
