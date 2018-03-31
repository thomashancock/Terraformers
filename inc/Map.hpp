#ifndef MAP_H
#define MAP_H

// STD
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <time.h> // Will need to move this later

// SFML
#include <SFML/Graphics.hpp>

// LOCAL
#include "Debug.hpp"
#include "SceneNode.hpp"
#include "Tile.hpp"
#include "Unit.hpp"
#include "HexGrid.hpp"

class Map :
public SceneNode
{
public:
	explicit Map(
		int mapSize
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
		sf::Vector2f position
	);
	void deselectTile();

	void updateHighlighting(
		sf::Vector2f worldMousePosition
	);

private:
	void setupMap();

	int getDistanceHexGrid(
		sf::Vector2i startCoors,
		sf::Vector2i endCoors
	);

private:
	HexGrid* m_grid;
	const int m_mapSize;

	// Selected object pointers
	Tile* m_selectedTile;
	Unit* m_selectedUnit;
};

#endif /* MAP_H */
