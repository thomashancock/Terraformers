#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "./SceneNode.hpp"
#include "./Tile.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>

class Map :
public SceneNode
{
public:
	explicit Map(
		int rows,
		int cols
	);

	void coorsToPosition(
		sf::Vector2<int>* position,
		int xCoor,
		int yCoor
	);

private:
	virtual unsigned int getCategory() const;

	void setupMap();

private:
	// Member variables here
	int m_rows;
	int m_cols;
	std::vector< std::vector< Tile* > > m_tileMap;
};

#endif /* MAP_H */