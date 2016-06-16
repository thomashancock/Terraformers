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
	Tile* getTile(
		sf::Vector2i coors
	);
	Tile* getTile(
		sf::Vector2f position
	);

	bool placeUnit(
		Unit* unit,
		int xCoor,
		int yCoor
	);
	bool placeUnit(
		Unit* unit,
		sf::Vector2i coors
	);

	void selectTile(
		int xCoor,
		int yCoor
	);
	void selectTile(
		sf::Vector2i coors
	);
	void selectTile(
		sf::Vector2f position
	);
	void deselectTile();

private:
	sf::Vector2f setTilePosition(
		int xCoor,
		int yCoor
	);

	sf::Vector2i positionToCoordinates(
		sf::Vector2f position
	);

	void setupMap();

private:
	// Map variables
	int m_rows;
	int m_cols;
	std::vector< std::vector< Tile* > > m_tileMap;

	// Selected object pointers
	Tile* m_selectedTile;
	Unit* m_selectedUnit;
};

#endif /* MAP_H */
