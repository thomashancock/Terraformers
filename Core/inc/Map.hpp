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
#include "Unit.hpp"
#include "TileBank.hpp"
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

private:
	HexGrid m_grid;
	TileBank* m_tileBank;

	// Selected object pointers
	Tile* m_selectedTile;
	Unit* m_selectedUnit;
};

#endif /* MAP_H */
