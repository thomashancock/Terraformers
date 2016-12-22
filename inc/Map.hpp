#ifndef MAP_H
#define MAP_H

#include "Debug.hpp"
#include <SFML/Graphics.hpp>
#include "./SceneNode.hpp"
#include "./Tile.hpp"
#include "./Unit.hpp"
#include "./HexGrid.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

class Map :
public SceneNode
{
public:
	explicit Map(
		int mapSize
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

	// void selectTile(
	// 	int xCoor,
	// 	int yCoor
	// );
	// void selectTile(
	// 	sf::Vector2i coors
	// );
	void selectTile(
		sf::Vector2f position
	);
	void deselectTile();

	void updateHighlighting(
		sf::Vector2f worldMousePosition
	);

private:
	// sf::Vector2f setTilePosition(
	// 	int xCoor,
	// 	int yCoor
	// );

	// sf::Vector2i positionToCoordinates(
	// 	sf::Vector2f position
	// );

	void setupMap();

	int getDistanceHexGrid(
		sf::Vector2i startCoors,
		sf::Vector2i endCoors
	);

	// int getMapColLength(
	// 	int row
	// );

private:
	// Map variables
	// const int m_mapSize;
	// int m_rows;
	// std::vector< std::vector< Tile* > > m_tileMap;

	HexGrid* m_grid;

	// Selected object pointers
	Tile* m_selectedTile;
	Unit* m_selectedUnit;
};

#endif /* MAP_H */
