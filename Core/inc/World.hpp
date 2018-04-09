#ifndef WORLD_H
#define WORLD_H

// STD
#include <array>
#include <iostream>

// SFML
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// LOCAL
#include "SceneNode.hpp"
#include "Map.hpp"
// #include "Unit.hpp"
// #include "CommandQueue.hpp"
// #include "Command.hpp"
// #include "Input.hpp"

class World :
private sf::NonCopyable
{
public:
	//! Constructor
	explicit World(
		sf::RenderWindow& window //!< Reference to the game window
	);

	//! Updates the world
	void update(
		sf::Time elapsedTime //!< Elapsed time since previous update
	);

	//! Draws the game world
	void draw();

	//! Command Queue getter
	// CommandQueue& getCommandQueue();

private:
	void buildScene();
	void processMousePosition(
		sf::Time elapsedTime
	);
	void updateViewPosition(
		sf::Vector2i mousePos,
		sf::Time elapsedTime
	);
	void processMouseClicks(
		sf::Time elapsedTime
	);

	// void newUnit();

private:
	enum Layer {
		Background,
		Front,
		LayerCount
	};

private:
	sf::RenderWindow& m_window;
	SceneNode m_sceneGraph;
	std::array<SceneNode*, LayerCount> m_sceneLayers;
	// CommandQueue m_commandQueue;
	sf::Vector2f m_worldMousePos;

	Map* m_map;
};

#endif /* WORLD_H */
