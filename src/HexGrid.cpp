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
			sf::Vector2i coordinates(iX,iY);
			if (getAtomicDistance(sf::Vector2i(0,0),coordinates) <= m_mapSize) {

				const sf::Vector2f position = coordinatesToPosition(coordinates);
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
	sf::Vector2i coors
) const {
	auto search = m_tiles.find(coors);
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
	sf::Vector2f position
) const {
	auto coors = positionToCoordinates(position);
	return getTile(coors);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool HexGrid::isValidCoordinate(
	sf::Vector2i coors
) const {
	if (coors.x > m_mapSize) return false;
	if (coors.x < -m_mapSize) return false;
	if (coors.y > m_mapSize) return false;
	if (coors.y < -m_mapSize) return false;

	auto zCoor = calcZCoor(coors);
	if (zCoor > m_mapSize) return false;
	if (zCoor < -m_mapSize) return false;

	return true;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int HexGrid::getAtomicDistance(
	const sf::Vector2i coor1,
	const sf::Vector2i coor2
) const {
	auto zCoor1 = calcZCoor(coor1);
	auto zCoor2 = calcZCoor(coor2);

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
int HexGrid::calcZCoor(
	const sf::Vector2i coors
) const {
	return -coors.x - coors.y;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Vector2f HexGrid::coordinatesToPosition(
	const sf::Vector2i coors
) const {
	// Calculate tile position using 3D coordinate system:
	const static float sqrt3 = std::sqrt(3.0);

	const int zCoor = calcZCoor(coors);
	const float sideLength = 36.0; // *** Need to unify with tiles

	const float xPos =
		coors.x * sqrt3*sideLength/2.0 +
		zCoor   * -sqrt3*sideLength/2.0;

	const float yPos =
		coors.x * -sideLength/2.0 +
		coors.y * sideLength +
		zCoor   * -sideLength/2.0;

	return sf::Vector2f(xPos,yPos);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Vector2i HexGrid::positionToCoordinates(
	sf::Vector2f position
) const {

	const float sideLength = 36.0; // *** Need to unify with tiles

	// Make educated guess at which tile is under the mouse
	const static float sqrt3 = std::sqrt(3.0);
	const int xCoor = static_cast<int>(
		(sqrt3*position.x - position.y) / (3.0*sideLength)
	);
	const int yCoor = static_cast<int>(2.0 * position.y / (3.0*sideLength));

	sf::Vector2i tileCoors(xCoor,yCoor);

	// Search Neighbouring tiles to find closest
	static auto getAbsDist = [] (
		const sf::Vector2f& vector1,
		const sf::Vector2f& vector2
	) -> double {
		const auto disp = vector1 - vector2;
		return std::sqrt(disp.x*disp.x + disp.y*disp.y);
	};

	double minDist = 20.0*sideLength;
	for (int iX = xCoor-1; iX <= xCoor+1; iX += 1) {
		for (int iY = yCoor-1; iY <= yCoor+1; iY += 1) {
			sf::Vector2i tmpCoors(iX,iY);
			const auto dist = getAbsDist(coordinatesToPosition(tmpCoors),position);
			if (dist < minDist) {
				minDist = dist;
				tileCoors = tmpCoors;
			}
		}
	}

	// Return closest tile to mouse
	return tileCoors;
}
