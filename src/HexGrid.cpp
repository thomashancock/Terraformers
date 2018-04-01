#include "HexGrid.hpp"

// STD
#include <cmath>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Public:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
HexGrid::HexGrid(
	int mapSize
) :
	m_mapSize(mapSize),
	m_rows(2 * m_mapSize - 1)
{
	STD_LOG("Creating Map");

	for (int iX = -m_mapSize; iX <= m_mapSize; ++iX) {
		for (int iY = -m_mapSize; iY <= m_mapSize; ++iY) {
			// for (int iZ = -m_mapSize; iZ <= m_mapSize; ++iZ) {
				const sf::Vector2f position = setTilePosition(iX,iY);
				// Create unique pointer to the tile
				std::unique_ptr<Tile> tile(new Tile(Tile::Basic,sf::Vector2i(iX,iY),position));
				// Copy the unique pointer to a regular pointer
				Tile* tilePtr = tile.get();
				// Attach unique pointer as sceneNode child
				this->attachChild(std::move(tile));
				// Store regular pointer in tile map
				m_tiles.insert(std::make_pair(sf::Vector2i(iX,iY),tilePtr));
			// }
		}
	}

	// for (int i = 0; i < m_rows; i++) {
	// 	std::vector<Tile*> mapRow;
  //
	// 	const int numCols = getGridColLength(i);
	// 	ASSERT(numCols > 0);
	// 	for (int j = 0; j < numCols; j++) {
	// 		const sf::Vector2f position = setTilePosition(i,j);
	// 		// Create unique pointer to the tile
	// 		std::unique_ptr<Tile> tile(new Tile(Tile::Basic,position.x,position.y));
	// 		// Copy the unique pointer to a regular pointer
	// 		Tile* tilePtr = tile.get();
	// 		// Attach unique pointer as sceneNode child
	// 		this->attachChild(std::move(tile));
	// 		// Store regular pointer in tile array vector
	// 		mapRow.push_back(tilePtr);
	// 	}
	// 	// Store row vector in vector of vectors
	// 	m_tileMap.push_back(mapRow);
	// }
	STD_LOG("Finished Creating Map");
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* HexGrid::getTile(
	int xCoor,
	int yCoor
) const {
	ASSERT(xCoor >= -m_mapSize);
	ASSERT(xCoor <= m_mapSize);
	ASSERT(yCoor >= -m_mapSize);
	ASSERT(yCoor <= m_mapSize);

	try {
		auto ptr = m_tiles.at(sf::Vector2i(xCoor,yCoor));
		return ptr;
	} catch (std::exception& e) {
		STD_ERR(e.what());
		ASSERT(false && "Tile map lookup out of range");
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
	sf::Vector2i coors = positionToVectorIndicies(position);

	// *** Need to implement
	return nullptr;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool HexGrid::isValidCoordinate(
	int xCoor,
	int yCoor
) const {
	int yTmp = yCoor;
	if (xCoor >= m_mapSize) {
		yTmp -= (xCoor - m_mapSize + 1);
	}

	if (xCoor < 0) return false;
	if (yTmp < 0) return false;
	if (xCoor >= m_rows) return false;
	if (yTmp >= getGridColLength(xCoor)) return false;
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
// -----------------------------------------------------------------------------
// Private:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
sf::Vector2f HexGrid::setTilePosition(
	int xCoor,
	int yCoor
	) {
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

	sf::Vector2f position(xPos,yPos);
	// const int spacing = 1; // Adds white space between the tiles
  //
	// // Need to shift tiles beyond x >= mapSize accross to complete hexagon shape
	// int yTmp = yCoor;
	// if (xCoor >= m_mapSize) {
	// 	yTmp += (xCoor - m_mapSize + 1);
	// }
  //
	// position.x = (72-16+spacing)*(xCoor - yTmp);
	// position.y = (31+spacing)*(xCoor + yTmp);

	return position;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Vector2i HexGrid::positionToVectorIndicies(
	sf::Vector2f position
) const {
	// Determine tile position by solving pair of equations:
	// x_p = C_x * (x_c + y_c)
	// y_p = C_y * (x_c - y_c)

	const int spacing = 1;
	const double xTmp = position.x / static_cast<double>(72-16+spacing);
	const double yTmp = position.y / static_cast<double>(30+spacing);

	sf::Vector2i coors;

	coors.x = std::round((xTmp + yTmp)/2.0);
	coors.y = std::round((yTmp - xTmp)/2.0);

	if (coors.x >= m_mapSize) {
		coors.y -= (coors.x - m_mapSize + 1);
	}

	return coors;
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
) {
	return 0 - xCoor - yCoor;
}
