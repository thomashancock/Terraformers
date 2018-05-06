#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

// STD
#include <memory>

// SFML
#include <SFML/Graphics.hpp>

// LOCAL
#include "System.hpp"
#include "GraphicsComponent.hpp"

class GraphicsSystem :
	public System
{
public:
	GraphicsSystem(
		sf::RenderWindow& window
	);

	void update() final override;

	void registerComponent(
		std::shared_ptr<GraphicsComponent> component
	);

private:
	sf::RenderWindow& m_window;

	std::vector< std::weak_ptr<GraphicsComponent> > m_components;
};

#endif /* GRAPHICSSYSTEM_H */
