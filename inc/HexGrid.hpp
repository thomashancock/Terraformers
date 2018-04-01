#ifndef HEXGRID_H
#define HEXGRID_H

// STD
#include <utility>
#include <map>

// SFML
#include <SFML/System.hpp>

// LOCAL
#include "Debug.hpp"
#include "Tile.hpp"
#include "SceneNode.hpp"

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

	int calcZCoor(
		const int xCoor,
		const int yCoor
	);

private:
	const int m_mapSize;
	const int m_rows;

	// std::vector< std::vector< Tile* > > m_tileMap;

	// Comparitor for Vector2i to facilitate map storage
	struct compareVector2i {
		bool operator() (
			const sf::Vector2i& a,
			const sf::Vector2i& b
		) const {
			if (a.x != b.x) {
				return a.x < b.x;
			} else {
				return a.y < b.y;
			}
		}
	};

	std::map< sf::Vector2i, Tile*, compareVector2i > m_tiles;
};

#endif /* HEXGRID_H */
