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

	Tile* getTile(
		int xCoor,
		int yCoor
	) const;
	Tile* getTile(
		sf::Vector2i coors
	) const;
	Tile* getTile(
		sf::Vector2f position
	) const;

	bool isValidCoordinate(
		int xCoor,
		int yCoor
	) const;
	bool isValidCoordinate(
		sf::Vector2i coors
	) const;

private:
	sf::Vector2f setTilePosition(
		int xCoor,
		int yCoor
	);

	sf::Vector2i positionToVectorIndicies(
		sf::Vector2f position
	) const;

	int getGridColLength(
		int row
	) const;

private:
	const int m_mapSize;
	const int m_rows;
	std::vector< std::vector< Tile* > > m_tileMap;
};

#endif /* HEXGRID_H */
