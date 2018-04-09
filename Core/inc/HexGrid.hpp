#ifndef HEXGRID_H
#define HEXGRID_H

// SFML
#include <SFML/System.hpp>

class HexGrid {
public:
	explicit HexGrid(
		int mapSize
	);

	const int getMapSize() const { return m_mapSize; }

	bool isValidCoordinate(
		sf::Vector2i coors
	) const;

	int getAtomicDistance(
		const sf::Vector2i coor1,
		const sf::Vector2i coor2
	) const;

	sf::Vector2f coordinatesToPosition(
		const sf::Vector2i coors
	) const;

	sf::Vector2i positionToCoordinates(
		sf::Vector2f position
	) const;

private:
	int calcZCoor(
		const sf::Vector2i coors
	) const;

private:
	const int m_mapSize;
};

#endif /* HEXGRID_H */
