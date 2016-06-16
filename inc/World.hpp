#ifndef WORLD_H
#define WORLD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>

#include "SceneNode.hpp"
#include "Tile.hpp"
#include "Map.hpp"
#include "Unit.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"
#include "Input.hpp"

class World :
private sf::NonCopyable
{
public:
	explicit World(
		sf::RenderWindow& window
	);

	void update(
		sf::Time elapsedTime
	);

	void draw();

	CommandQueue& getCommandQueue();

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
	CommandQueue m_commandQueue;
	sf::Vector2f m_worldMousePos;

	Tile* m_hoveredTile;
	Tile* m_selectedTile;
	Map* m_map;
	Unit* m_testUnit;
};

#endif /* WORLD_H */
