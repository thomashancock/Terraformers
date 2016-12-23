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
	std::unique_ptr<HexGrid> hexGrid(new HexGrid(mapSize));
	m_grid = hexGrid.get();
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
		unit->setCoors(xCoor,yCoor);
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
	// for (int i = 0; i < m_grid->getRows(); i++) {
	// 	for (int j = 0; j < m_grid->getCols(i); j++) {
			// m_grid->getTile(i,j)->unhighlight();
		// }
	// }

	// Highlight tiles according to mouse positions
	Tile* hoveredTile = m_grid->getTile(worldMousePosition);
	int radius = 0;
	if (hoveredTile == m_selectedTile) {
		if (NULL != m_selectedUnit) {
			radius = m_selectedUnit->getRemainingMoves();
			sf::Vector2i unitCoors = m_selectedUnit->getCoors();
			for (int i = unitCoors.x - radius; i < unitCoors.x + radius + 1; i++) {
				for (int j = unitCoors.y - radius; j < unitCoors.y + radius + 1; j++) {
					if (true == m_grid->isValidCoordinate(i,j)) {
						sf::Vector2i tileCoors(i,j);
						if (getDistanceHexGrid(tileCoors,unitCoors) <= radius) {
							m_grid->getTile(i,j)->highlight();
						}
					}
				}
			}
		}
	} else {
		radius = 0;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Private:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Map::setupMap() {
	STD_LOG("Populating Map");
	for (int i = 0; i < m_mapSize; i++) {
		// Top Right Edge
		m_grid->getTile(i,0)->setType(Tile::Border);
		// Top Left Edge
		m_grid->getTile(0,i)->setType(Tile::Border);
		// Right Edge
		m_grid->getTile(m_mapSize+i-1,i)->setType(Tile::Border);
		// Left Edge
		m_grid->getTile(i,m_mapSize+i-1)->setType(Tile::Border);
		// Bottom Right Edge
		m_grid->getTile(2*(m_mapSize-1),m_mapSize+i-1)->setType(Tile::Border);
		// Bottom Left Edge
		m_grid->getTile(m_mapSize+i-1,2*(m_mapSize-1))->setType(Tile::Border);
	}

	// Randomly define Forest and Mountain
	srand(time(NULL)); // Will need to move this later
	const sf::Vector2i mapMiddle(m_mapSize-1,m_mapSize-1);
	sf::Vector2i greenStart(m_mapSize-1,m_mapSize-1);
	while(getDistanceHexGrid(mapMiddle,greenStart) < 2) {
		greenStart.x = (int) ((rand()/RAND_MAX) * (m_mapSize - 1)) + 1;
		greenStart.y = (int) ((rand()/RAND_MAX) * (m_mapSize - 1)) + 1;
	}
	STD_LOG("Green Start: " << greenStart.x << ", " << greenStart.y);
	m_grid->getTile(greenStart)->setType(Tile::Forest);

	sf::Vector2i redStart(m_mapSize-1,m_mapSize-1);
	while(getDistanceHexGrid(mapMiddle,redStart) < 2) {
		redStart.x = (2*(m_mapSize-1)) - 1 - (int) ((rand()/RAND_MAX) * (m_mapSize - 1));
		redStart.y = (2*(m_mapSize-1)) - 1 - (int) ((rand()/RAND_MAX) * (m_mapSize - 1));
	}
	STD_LOG("Red Start: " << greenStart.x << ", " << greenStart.y);
	m_grid->getTile(redStart)->setType(Tile::Mountain);
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
