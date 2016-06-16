#ifndef MAP_H
#define MAP_H

#include "Debug.hpp"
#include <SFML/Graphics.hpp>
#include "./SceneNode.hpp"
#include "./Tile.hpp"
#include "./Unit.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

class Map :
public SceneNode
{
public:
	explicit Map(
		int rows,
		int cols
	);

	Tile* getTile(
		int xCoor,
		int yCoor
	);
	Tile* getTileAtPosition(
		sf::Vector2f position
	);

	bool placeUnit(
		Unit* unit,
		int xCoor,
		int yCoor
	);

private:
	sf::Vector2f setTilePosition(
		int xCoor,
		int yCoor
	);

	void setupMap();

private:
	// Member variables here
	int m_rows;
	int m_cols;
	std::vector< std::vector< Tile* > > m_tileMap;
};

#endif /* MAP_H */
