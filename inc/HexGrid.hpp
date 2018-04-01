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
		const sf::Vector2i coors
	) const;

	Tile* getTile(
		const sf::Vector2f position
	) const;

	bool isValidCoordinate(
		sf::Vector2i coors
	) const;

	int getAtomicDistance(
		const sf::Vector2i coor1,
		const sf::Vector2i coor2
	) const;

	void unhighlightAll();

private:
	int calcZCoor(
		const sf::Vector2i coors
	) const;

	sf::Vector2f coordinatesToPosition(
		const sf::Vector2i coors
	) const;

	sf::Vector2i positionToCoordinates(
		sf::Vector2f position
	) const;

private:
	const int m_mapSize;

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
