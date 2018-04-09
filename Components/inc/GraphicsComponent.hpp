#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

// SFML
#include <SFML/Graphics.hpp>

// LOCAL
#include "Component.hpp"

class GraphicsComponent :
	Component
{
public:
	GraphicsComponent(
		sf::ConvexShape& sprite
	);

	void draw(
		sf::RenderTarget& target
	) const;

private:
	sf::ConvexShape m_sprite;
};

#endif /* GRAPHICSCOMPONENT_H */
