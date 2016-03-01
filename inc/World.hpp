#ifndef WORLD_H
#define WORLD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>

#include "SceneNode.hpp"
#include "Tile.hpp"
#include "Map.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"

class World :
private sf::NonCopyable
{
public:
	explicit World(
		sf::RenderWindow& window
	);

	void update(
		sf::Time dt
	);
	
	void draw();

	CommandQueue& getCommandQueue();

private:
	void buildScene();

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

	Tile* m_testTile;
	Map* m_map;
};


#endif /* WORLD_H */