#ifndef HEXGRID_H
#define HEXGRID_H

#include "Debug.hpp"
#include <SFML/Graphics.hpp>
#include "./SceneNode.hpp"
#include "./Tile.hpp"

#include <vector>
#include <cmath>

class HexGrid :
public SceneNode
{
public:
	explicit HexGrid(
		int mapSize
	);

	int getRows();
	int getCols(
		int row
	);

	Tile* getTile(
		int xCoor,
		int yCoor
	);
	Tile* getTile(
		sf::Vector2i coors
	);
	Tile* getTile(
		sf::Vector2f position
	);

private:
	sf::Vector2f setTilePosition(
		int xCoor,
		int yCoor
	);

	sf::Vector2i positionToVectorIndicies(
		sf::Vector2f position
	);

	int getGridColLength(
		int row
	);

private:
	// Map variables
	const int m_mapSize;
	int m_rows;
	std::vector< std::vector< Tile* > > m_tileMap;
};

#endif /* HEXGRID_H */
