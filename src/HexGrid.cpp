#include "HexGrid.hpp"

// STD
#include <cmath>
#include <algorithm>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Public:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
HexGrid::HexGrid(
	int mapSize
) :
	m_mapSize(mapSize)
{
	STD_LOG("Creating Map");

	for (int iX = -m_mapSize; iX <= m_mapSize; ++iX) {
		for (int iY = -m_mapSize; iY <= m_mapSize; ++iY) {
			if (getAtomicDistance(sf::Vector2i(0,0),sf::Vector2i(iX,iY)) <= m_mapSize) {

				const sf::Vector2f position = calcTilePosition(iX,iY);
				// Create unique pointer to the tile
				std::unique_ptr<Tile> tile(new Tile(Tile::Basic,sf::Vector2i(iX,iY),position));
				// Copy the unique pointer to a regular pointer
				Tile* tilePtr = tile.get();
				// Attach unique pointer as sceneNode child
				this->attachChild(std::move(tile));
				// Store regular pointer in tile map
				m_tiles.insert(std::make_pair(sf::Vector2i(iX,iY),tilePtr));
			}
		}
	}

	STD_LOG("Finished Creating Map");
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* HexGrid::getTile(
	int xCoor,
	int yCoor
) const {
	// ASSERT(xCoor >= -m_mapSize);
	// ASSERT(xCoor <= m_mapSize);
	// ASSERT(yCoor >= -m_mapSize);
	// ASSERT(yCoor <= m_mapSize);

	auto search = m_tiles.find(sf::Vector2i(xCoor,yCoor));
	if (search != m_tiles.end()) {
		return search->second;
	}	else {
		return nullptr;
	}
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* HexGrid::getTile(
	sf::Vector2i coors
) const {
	return getTile(coors.x,coors.y);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* HexGrid::getTile(
	sf::Vector2f position
) const {
	auto coors = positionToVectorIndicies(position);
	return getTile(coors);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool HexGrid::isValidCoordinate(
	int xCoor,
	int yCoor
) const {
	if (xCoor > m_mapSize) return false;
	if (xCoor < -m_mapSize) return false;
	if (yCoor > m_mapSize) return false;
	if (yCoor < -m_mapSize) return false;

	auto zCoor = calcZCoor(xCoor,yCoor);
	if (zCoor > m_mapSize) return false;
	if (zCoor < -m_mapSize) return false;

	return true;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool HexGrid::isValidCoordinate(
	sf::Vector2i coors
) const {
	return isValidCoordinate(coors.x,coors.y);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int HexGrid::getAtomicDistance(
	const sf::Vector2i coor1,
	const sf::Vector2i coor2
) const {
	auto zCoor1 = calcZCoor(coor1.x,coor1.y);
	auto zCoor2 = calcZCoor(coor2.x,coor2.y);

	return std::max({
		std::abs(coor2.x - coor1.x),
		std::abs(coor2.y - coor1.y),
		std::abs(zCoor2 - zCoor1)
	});
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void HexGrid::unhighlightAll() {
	for (auto& entry : m_tiles) {
		entry.second->unhighlight();
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Private:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
sf::Vector2f HexGrid::calcTilePosition(
	int xCoor,
	int yCoor
) const {
	ASSERT(xCoor >= -m_mapSize);
	ASSERT(xCoor <= m_mapSize);
	ASSERT(yCoor >= -m_mapSize);
	ASSERT(yCoor <= m_mapSize);

	// Calculate tile position using 3D coordinate system:
	const static float sqrt3 = std::sqrt(3.0);

	const int zCoor = calcZCoor(xCoor,yCoor);
	const float sideLength = 36.0; // *** Need to unify with tiles

	const float xPos =
		xCoor * sqrt3*sideLength/2.0 +
		zCoor * -sqrt3*sideLength/2.0;

	const float yPos =
		xCoor * -sideLength/2.0 +
		yCoor * sideLength +
		zCoor * -sideLength/2.0;

	return sf::Vector2f(xPos,yPos);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Vector2i HexGrid::positionToVectorIndicies(
	sf::Vector2f position
) const {
	const static float sqrt3 = std::sqrt(3.0);

	const float sideLength = 36.0; // *** Need to unify with tiles

	float xCoor = (sqrt3*position.x - position.y) / (3.0*sideLength);

	// xCoor += sideLength/2.0;

	float yCoor = 2.0 * position.y / (3.0*sideLength);

	return sf::Vector2i(static_cast<int>(xCoor),static_cast<int>(yCoor));
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int HexGrid::getGridColLength(
	int row
) const {
	return (2*m_mapSize) - 1 - abs(row - m_mapSize + 1);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int HexGrid::calcZCoor(
	const int xCoor,
	const int yCoor
) const {
	return 0 - xCoor - yCoor;
}
