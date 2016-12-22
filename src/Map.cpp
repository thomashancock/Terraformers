#include "Map.hpp"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Public:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Map::Map(
	int rows,
	int cols
) {
	m_rows = rows;
	m_cols = cols;

	STD_LOG("Creating Map");
	for (int i = 0; i < m_rows; i++) {
		std::vector<Tile*> mapRow;
		for (int j = 0; j < m_cols; j++) {
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
	setupMap();
	STD_LOG("Finished Creating Map");

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
	ASSERT(yCoor < m_cols);
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
	ASSERT(coors.y < m_cols);
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
	if ((-1 < coors.x)&&(coors.x < m_rows)&&(-1 < coors.y)&&(coors.y < m_cols)) {
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
	ASSERT(yCoor < m_cols);
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
	ASSERT(coors.y < m_cols);
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
	ASSERT(yCoor < m_cols);
	if (NULL != m_selectedTile) {
		m_selectedTile->deselect();
	}
	if (NULL != m_selectedUnit) {
		m_selectedUnit = NULL;
	}
	m_selectedTile = getTile(xCoor,yCoor);
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
void Map::selectTile (
	sf::Vector2i coors
) {
	ASSERT(coors.x > -1);
	ASSERT(coors.y > -1);
	ASSERT(coors.x < m_rows);
	ASSERT(coors.y < m_cols);
	selectTile(coors.x,coors.y);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Map::selectTile(
	sf::Vector2f position
) {
	sf::Vector2i coors = positionToCoordinates(position);
	if ((-1 < coors.x)&&(coors.x < m_rows)&&(-1 < coors.y)&&(coors.y < m_cols)) {
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
		for (int j = 0; j < m_cols; j++) {
			getTile(i,j)->unhighlight();
		}
	}

	// Highlight tiles according to mouse positions
	sf::Vector2i mouseCoors = positionToCoordinates(worldMousePosition);
	if ((-1 < mouseCoors.x)&&(mouseCoors.x < m_rows)&&(-1 < mouseCoors.y)&&(mouseCoors.y < m_cols)) {
		Tile* hoveredTile = getTile(mouseCoors);
		int radius = 0;
		if (hoveredTile == m_selectedTile) {
			if (NULL != m_selectedUnit) {
				radius = m_selectedUnit->getRemainingMoves();
			}
		} else {
			radius = 0;
		}


		// for (int i = mouseCoors.x - radius; i < mouseCoors.x + radius + 1; i++) {
		// 	getTile(i,mouseCoors.y)->highlight();
		// }
		//
		// for (int j = mouseCoors.y - radius; j < mouseCoors.y + radius + 1; j++) {
		// 	getTile(mouseCoors.x,j)->highlight();
		// }
		for (int i = mouseCoors.x - radius + 1; i < mouseCoors.x + radius; i++) {
			for (int j = mouseCoors.y - radius; j < mouseCoors.y + radius + 1; j++) {
				if ((-1 < i)&&(i < m_rows)&&(-1 < j)&&(j < m_cols)) {
					getTile(i,j)->highlight();
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
	ASSERT(xCoor < m_rows);
	ASSERT(yCoor < m_cols);
	sf::Vector2f position;

	// // Calculate Hexagon position based on array position
	// position.x = 60*xCoor;
	// position.y = 31*yCoor;
	//
	// // Offset every other row to tessellate hexagons
	// if (0 == yCoor%2) {
	// 	position.x += 30;
	// }
	//
	// // Offset Hexagons from edge of screen
	// position.x += 40;
	// position.y += 40;

	const int spacing = 1;
	position.x = (72-16+spacing)*(xCoor + yCoor);
	position.y = (30+spacing)*(xCoor - yCoor);

	return position;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Vector2i Map::positionToCoordinates(
	sf::Vector2f position
	) {
	// // Determine the coordinates by applying the opposite procedure to calculating the positions
	// double xTmp = position.x - 40.0;
	// double yTmp = position.y - 40.0;
	//
	// yTmp /= 31.0;
	//
	// double fMod2 = fmod(yTmp,2.0);
	// if ((-0.5 < fMod2)&&(fMod2 < 0.5)) {
	// 	xTmp -= 30;
	// }
	//
	// xTmp /= 60;
	//
	// sf::Vector2i coors;
	// coors.x = (int) std::round(xTmp);
	// coors.y = (int) std::round(yTmp);
	//
	// // Correct for bug where tile right of correct tile is selected
	// if ((-1 < coors.x)&&(coors.x < m_rows)&&(-1 < coors.y)&&(coors.y < m_cols)) {
	// 	sf::Vector2f tilePos = getTile(coors)->getPosition();
	// 	if ((position.x < tilePos.x - 31)&&(0 < coors.x)) {
	// 		coors.x -= 1;
	// 	}
	// }

	const int spacing = 1;
	double xTmp = position.x / (double) (72-16+spacing);
	double yTmp = position.y / (double) (30+spacing);

	sf::Vector2i coors;

	coors.x = std::round((xTmp + yTmp)/2.0);
	coors.y = std::round((xTmp - yTmp)/2.0);

	return coors;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Map::setupMap() {
	STD_LOG("Populating Map");
	for (int i = 0; i < m_rows; i++) {
		getTile(i,0)->setType(Tile::Border);
		getTile(i,m_cols-1)->setType(Tile::Border);
	}
	for (int j = 1; j < m_cols-1; j++) {
		getTile(0,j)->setType(Tile::Border);
		getTile(m_rows-1,j)->setType(Tile::Border);
	}

	// Randomly define Forest and Mountain
	int randRow = (rand()%(m_rows-4))+2;
	int randCol = (rand()%(m_cols-4))+2;
	ASSERT(randRow > -1);
	ASSERT(randCol > -1);
	ASSERT(randRow < m_rows);
	ASSERT(randCol < m_cols);
	getTile(randRow,randCol)->setType(Tile::Forest);

	randRow = (rand()%(m_rows-4))+2;
	randCol = (rand()%(m_cols-4))+2;
	ASSERT(randRow > -1);
	ASSERT(randCol > -1);
	ASSERT(randRow < m_rows);
	ASSERT(randCol < m_cols);
	getTile(randRow,randCol)->setType(Tile::Mountain);
}
