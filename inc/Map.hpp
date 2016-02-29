#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "./SceneNode.hpp"
#include "./Tile.hpp"

#include <iostream>
#include <vector>

class Map :
public SceneNode
{
public:
	explicit Map(
		int rows,
		int cols
	);

private:
	virtual unsigned int getCategory() const;

	void setTilePositions();

private:
	// Member variables here
	int m_rows;
	int m_cols;
	std::vector< std::vector< Tile* > > m_tileMap;
};

#endif /* MAP_H */