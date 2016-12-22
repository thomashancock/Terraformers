#include "Map.hpp"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Public:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Map::Map(
	int mapSize
) {
	std::unique_ptr<HexGrid> hexGrid(new HexGrid(mapSize));
	// Copy the unique pointer to a regular pointer
	m_grid = hexGrid.get();
	// Attach unique pointer as sceneNode child
	this->attachChild(std::move(hexGrid));

	setupMap();

	m_selectedTile = NULL;
	m_selectedUnit = NULL;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Map::placeUnit(
	Unit* unit,
	int xCoor,
	int yCoor
) {
	ASSERT(NULL != unit);

	bool unitPlaced = m_grid->getTile(xCoor,yCoor)->attachUnit(unit);
	if (true == unitPlaced) {
		sf::Vector2f unitPos = m_grid->getTile(xCoor,yCoor)->getPosition();
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
	ASSERT(NULL != unit);

	return placeUnit(unit,coors.x,coors.y);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Map::selectTile (
	sf::Vector2f position
) {
	if (NULL != m_selectedTile) {
		m_selectedTile->deselect();
	}
	if (NULL != m_selectedUnit) {
		m_selectedUnit = NULL;
	}
	m_selectedTile = m_grid->getTile(position);
	ASSERT(NULL != m_selectedTile);
	m_selectedTile->select();

	// Select associated unit if exists
	if (NULL != m_selectedTile->getUnit()) {
		m_selectedUnit = m_selectedTile->getUnit();
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
	for (int i = 0; i < m_grid->getRows(); i++) {
		for (int j = 0; j < m_grid->getCols(i); j++) {
			// m_grid->getTile(i,j)->unhighlight();
		}
	}

	// Highlight tiles according to mouse positions
	Tile* hoveredTile = m_grid->getTile(worldMousePosition);
	int radius = 0;
	if (hoveredTile == m_selectedTile) {
		if (NULL != m_selectedUnit) {
			radius = m_selectedUnit->getRemainingMoves();
		}
	} else {
		radius = 0;
	}

	// for (int i = mouseCoors.x - radius; i < mouseCoors.x + radius + 1; i++) {
	// 	for (int j = mouseCoors.y - radius; j < mouseCoors.y + radius + 1; j++) {
	// 		if ((-1 < i)&&(i < m_rows)&&(-1 < j)&&(j < getMapColLength(i))) {
	// 			sf::Vector2i tileCoors(i,j);
	// 			if (getDistanceHexGrid(tileCoors,mouseCoors) <= radius) {
	// 				m_grid->getTile(i,j)->highlight();
	// 			}
	// 		}
	// 	}
	// }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Private:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Map::setupMap() {
	STD_LOG("Populating Map");
	for (int i = 0; i < m_grid->getRows(); i++) {
		// m_grid->getTile(i,0)->setType(Tile::Border);
		// m_grid->getTile(i,m_grid->getCols(i)-1)->setType(Tile::Border);
	}
	// for (int j = 1; j < m_cols-1; j++) {
	// 	getTile(0,j)->setType(Tile::Border);
	// 	getTile(m_rows-1,j)->setType(Tile::Border);
	// }

	// Randomly define Forest and Mountain
	// int randRow = (rand()%(m_rows-4))+2;
	// int randCol = (rand()%(getMapColLength(randRow)-4))+2;
	// ASSERT(randRow > -1);
	// ASSERT(randCol > -1);
	// ASSERT(randRow < m_rows);
	// ASSERT(randCol < getMapColLength(randRow));
	// m_grid->getTile(randRow,randCol)->setType(Tile::Forest);

	// randRow = (rand()%(m_rows-4))+2;
	// randCol = (rand()%(getMapColLength(randRow)-4))+2;
	// ASSERT(randRow > -1);
	// ASSERT(randCol > -1);
	// ASSERT(randRow < m_rows);
	// ASSERT(randCol < getMapColLength(randRow));
	// m_grid->getTile(randRow,randCol)->setType(Tile::Mountain);
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
