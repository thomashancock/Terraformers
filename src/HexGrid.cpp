#include "HexGrid.hpp"

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
	m_rows = (2*m_mapSize) - 1;

	STD_LOG("Creating Map");
	m_rows = (2*m_mapSize) - 1;
	for (int i = 0; i < m_rows; i++) {
		std::vector<Tile*> mapRow;

		int numCols = getGridColLength(i);
		STD_LOG(i << ", " << numCols);
		ASSERT(numCols > 0);
		for (int j = 0; j < numCols; j++) {
			sf::Vector2f position = setTilePosition(i,j);
			// Create unique pointer to the tile
			std::unique_ptr<Tile> tile(new Tile(Tile::Basic,position.x,position.y));
			// Copy the unique pointer to a regular pointer
			Tile* tilePtr = tile.get();
			// Attach unique pointer as sceneNode child
			this->attachChild(std::move(tile));
			// Store regular pointer in tile array vector
			mapRow.push_back(tilePtr);
		}
		// Store row vector in vector of vectors
		m_tileMap.push_back(mapRow);
	}
	STD_LOG("Finished Creating Map");
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int HexGrid::getRows() {
	return m_rows;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int HexGrid::getCols(
	int row
) {
	return getGridColLength(row);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* HexGrid::getTile(
	int xCoor,
	int yCoor
) {
	ASSERT(-1 < xCoor);
	ASSERT(-1 < yCoor);
	ASSERT(xCoor < m_rows);
	ASSERT(yCoor < getGridColLength(xCoor));
	return 	m_tileMap.at(xCoor).at(yCoor);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* HexGrid::getTile(
	sf::Vector2i coors
) {
	ASSERT(-1 < coors.x);
	ASSERT(-1 < coors.y);
	ASSERT(coors.x < m_rows);
	ASSERT(coors.y < getGridColLength(coors.x));
	return getTile(coors.x,coors.y);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* HexGrid::getTile(
	sf::Vector2f position
) {
	sf::Vector2i coors = positionToVectorIndicies(position);

	// Ensure Tile coordinates are valid
	if ((-1 < coors.x)&&(coors.x < m_rows)&&(-1 < coors.y)&&(coors.y < getGridColLength(coors.x))) {
		return getTile(coors);
	} else {
		return NULL;
	}
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
	ASSERT(xCoor > -1);
	ASSERT(yCoor > -1);

	// Calculate tile position using equations:
	// x_p = C_x * (x_c + y_c)
	// y_p = C_y * (x_c - y_c)
	// C_x and C_y are determined using the size of the tile:
	// /--\
	// \__/
	// 72 is the width along the centre of the tile
	// 16 is the x component of the slant ( / )
	// 30 is the y component of the slant ( / )

	sf::Vector2f position;
	const int spacing = 1; // Adds white space between the tiles

	// Need to shift tiles beyond x >= mapSize accross to complete hexagon shape
	int yTmp = yCoor;
	if (xCoor >= m_mapSize) {
		yTmp += (xCoor - m_mapSize + 1);
	}

	position.x = (72-16+spacing)*(xCoor - yTmp);
	position.y = (30+spacing)*(xCoor + yTmp);

	return position;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Vector2i HexGrid::positionToVectorIndicies(
	sf::Vector2f position
	) {
	// Determine tile position by solving pair of equations:
	// x_p = C_x * (x_c + y_c)
	// y_p = C_y * (x_c - y_c)

	const int spacing = 1;
	double xTmp = position.x / (double) (72-16+spacing);
	double yTmp = position.y / (double) (30+spacing);

	sf::Vector2i coors;

	coors.x = std::round((xTmp + yTmp)/2.0);
	coors.y = std::round((yTmp - xTmp)/2.0);

	if (coors.x >= m_mapSize) {
		coors.y -= (coors.x - m_mapSize + 1);
	}

	STD_LOG(coors.x << ", " << coors.y);
	return coors;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int HexGrid::getGridColLength(
	int row
) {
	return (2*m_mapSize) - 1 - abs(row - m_mapSize + 1);
}
