#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System.hpp>

#include "Debug.hpp"
#include "Input.hpp"

class Command {
public:
	Command(
		Input::Type type
	);

	Input::Type getType() {
		return m_type;
	};

private:
	Input::Type m_type;
};

#endif /* COMMAND_HPP */
