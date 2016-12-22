#include "Map.hpp"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Public:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Map::Map(
	int mapSize
) :
m_mapSize(mapSize)
{
	m_rows = (2*m_mapSize) - 1;

	STD_LOG("Creating Map");
	m_rows = (2*m_mapSize) - 1;
	for (int i = 0; i < m_rows; i++) {
		std::vector<Tile*> mapRow;

		int numCols = getMapColLength(i);
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
	setupMap();

	m_selectedTile = NULL;
	m_selectedUnit = NULL;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* Map::getTile(
	int xCoor,
	int yCoor
) {
	ASSERT(-1 < xCoor);
	ASSERT(-1 < yCoor);
	ASSERT(xCoor < m_rows);
	ASSERT(yCoor < getMapColLength(xCoor));
	return 	m_tileMap.at(xCoor).at(yCoor);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* Map::getTile(
	sf::Vector2i coors
) {
	ASSERT(-1 < coors.x);
	ASSERT(-1 < coors.y);
	ASSERT(coors.x < m_rows);
	ASSERT(coors.y < getMapColLength(coors.x));
	return getTile(coors.x,coors.y);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* Map::getTile(
	sf::Vector2f position
) {
	sf::Vector2i coors = positionToCoordinates(position);

	// Ensure Tile coordinates are valid
	if ((-1 < coors.x)&&(coors.x < m_rows)&&(-1 < coors.y)&&(coors.y < getMapColLength(coors.x))) {
		return getTile(coors);
	} else {
		return NULL;
	}
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Map::placeUnit(
	Unit* unit,
	int xCoor,
	int yCoor
) {
	ASSERT(xCoor > -1);
	ASSERT(yCoor > -1);
	ASSERT(xCoor < m_rows);
	ASSERT(yCoor < getMapColLength(xCoor));
	ASSERT(NULL != unit);

	bool unitPlaced = getTile(xCoor,yCoor)->attachUnit(unit);
	if (true == unitPlaced) {
		sf::Vector2f unitPos = getTile(xCoor,yCoor)->getPosition();
		unit->setPosition(unitPos);
		return true;
	} else {
		return false;
	}
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Map::placeUnit(
	Unit* unit,
	sf::Vector2i coors
) {
	ASSERT(coors.x > -1);
	ASSERT(coors.y > -1);
	ASSERT(coors.x < m_rows);
	ASSERT(coors.y < getMapColLength(coors.x));
	ASSERT(NULL != unit);

	return placeUnit(unit,coors.x,coors.y);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Map::selectTile (
	int xCoor,
	int yCoor
) {
	ASSERT(xCoor > -1);
	ASSERT(yCoor > -1);
	ASSERT(xCoor < m_rows);
	ASSERT(yCoor < getMapColLength(xCoor));
	if (NULL != m_selectedTile) {
		m_selectedTile->deselect();
	}
	if (NULL != m_selectedUnit) {
		m_selectedUnit = NULL;
	}
	m_selectedTile = getTile(xCoor,yCoor);
	ASSERT(NULL != m_selectedTile);
	m_selectedTile->select();
	STD_LOG("Tile Selected: " << xCoor << ", " << yCoor);

	// Select associated unit if exists
	if (NULL != m_selectedTile->getUnit()) {
		m_selectedUnit = m_selectedTile->getUnit();
	}
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Map::selectTile (
	sf::Vector2i coors
) {
	ASSERT(coors.x > -1);
	ASSERT(coors.y > -1);
	ASSERT(coors.x < m_rows);
	ASSERT(coors.y < getMapColLength(coors.x));
	selectTile(coors.x,coors.y);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Map::selectTile(
	sf::Vector2f position
) {
	sf::Vector2i coors = positionToCoordinates(position);
	if ((-1 < coors.x)&&(coors.x < m_rows)&&(-1 < coors.y)&&(coors.y < getMapColLength(coors.x))) {
		selectTile(coors);
	}
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Map::deselectTile() {
	if (NULL != m_selectedUnit) {
		m_selectedUnit = NULL;
	}

	if (NULL != m_selectedTile) {
		m_selectedTile->deselect();
		m_selectedTile = NULL;
	}
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Map::updateHighlighting(
	sf::Vector2f worldMousePosition
) {
	// Unhighlight all tiles
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < getMapColLength(i); j++) {
			getTile(i,j)->unhighlight();
		}
	}

	// Highlight tiles according to mouse positions
	sf::Vector2i mouseCoors = positionToCoordinates(worldMousePosition);
	if ((-1 < mouseCoors.x)&&(mouseCoors.x < m_rows)&&(-1 < mouseCoors.y)&&(mouseCoors.y < getMapColLength(mouseCoors.x))) {
		Tile* hoveredTile = getTile(mouseCoors);
		int radius = 0;
		if (hoveredTile == m_selectedTile) {
			if (NULL != m_selectedUnit) {
				radius = m_selectedUnit->getRemainingMoves();
			}
		} else {
			radius = 0;
		}

		for (int i = mouseCoors.x - radius; i < mouseCoors.x + radius + 1; i++) {
			for (int j = mouseCoors.y - radius; j < mouseCoors.y + radius + 1; j++) {
				if ((-1 < i)&&(i < m_rows)&&(-1 < j)&&(j < getMapColLength(i))) {
					sf::Vector2i tileCoors(i,j);
					if (getDistanceHexGrid(tileCoors,mouseCoors) <= radius) {
						getTile(i,j)->highlight();
					}
				}
			}
		}
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Private:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
sf::Vector2f Map::setTilePosition(
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
sf::Vector2i Map::positionToCoordinates(
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
void Map::setupMap() {
	STD_LOG("Populating Map");
	for (int i = 0; i < m_rows; i++) {
		getTile(i,0)->setType(Tile::Border);
		getTile(i,getMapColLength(i)-1)->setType(Tile::Border);
	}
	// for (int j = 1; j < m_cols-1; j++) {
	// 	getTile(0,j)->setType(Tile::Border);
	// 	getTile(m_rows-1,j)->setType(Tile::Border);
	// }

	// Randomly define Forest and Mountain
	int randRow = (rand()%(m_rows-4))+2;
	int randCol = (rand()%(getMapColLength(randRow)-4))+2;
	ASSERT(randRow > -1);
	ASSERT(randCol > -1);
	ASSERT(randRow < m_rows);
	ASSERT(randCol < getMapColLength(randRow));
	getTile(randRow,randCol)->setType(Tile::Forest);

	randRow = (rand()%(m_rows-4))+2;
	randCol = (rand()%(getMapColLength(randRow)-4))+2;
	ASSERT(randRow > -1);
	ASSERT(randCol > -1);
	ASSERT(randRow < m_rows);
	ASSERT(randCol < getMapColLength(randRow));
	getTile(randRow,randCol)->setType(Tile::Mountain);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int Map::getDistanceHexGrid(
	sf::Vector2i startCoors,
	sf::Vector2i endCoors
) {
	sf::Vector2i distance;
	distance.x = startCoors.x - endCoors.x;
	distance.y = startCoors.y - endCoors.y;

	// Account for grid deformation in (n, -n) direction
	sf::Vector2i diagonalComp;
	int lesserCoor = abs(distance.x) < abs(distance.y) ? abs(distance.x) : abs(distance.y);
	diagonalComp.x = (distance.x < 0) ? -1*lesserCoor : lesserCoor;
	diagonalComp.y = (distance.y < 0) ? -1*lesserCoor : lesserCoor;

	sf::Vector2i straightComp;
	straightComp.x = distance.x - diagonalComp.x;
	straightComp.y = distance.y - diagonalComp.y;
	ASSERT((0 == straightComp.x)||(0 == straightComp.y));

	int straightDistance = abs(straightComp.x) + abs(straightComp.y);
	int diagonalDistance = abs(diagonalComp.x);

	// Check if diagonal is along deformed axis
	if (diagonalComp.x * diagonalComp.y < 0) {
		diagonalDistance *= 2;
	}

	return straightDistance + diagonalDistance;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int Map::getMapColLength(
	int row
) {
	return (2*m_mapSize) - 1 - abs(row - m_mapSize + 1);
}
