#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System.hpp>

#include "Debug.hpp"
#include <functional>

#include "Category.hpp"

class SceneNode;

struct Command {
	Command();
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=] (SceneNode& node, sf::Time dt)
	{
		// Check that the cast is safe
		ASSERT(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke the function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif /* COMMAND_HPP */
