#include "Map.hpp"

// Public:
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

Tile* Map::getTile(
	sf::Vector2i coors
	) {
	return getTile(coors.x,coors.y);
}

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

bool Map::placeUnit(
	Unit* unit,
	sf::Vector2i coors
	) {
	return placeUnit(unit,coors.x,coors.y);
}

void Map::selectTile(
	int xCoor,
	int yCoor
	) {
	if (NULL != m_selectedTile) {
		m_selectedTile->deselect();
	}
	m_selectedTile = getTile(xCoor,yCoor);
	ASSERT(NULL != m_selectedTile);
	m_selectedTile->select();

	// Select associated unit if exists
	if (NULL != m_selectedTile->getUnit()) {
		m_selectedUnit = m_selectedTile->getUnit();
	}
}

// Private:
sf::Vector2f Map::setTilePosition(
	int xCoor,
	int yCoor
	) {
	ASSERT(xCoor > -1);
	ASSERT(yCoor > -1);
	ASSERT(xCoor < m_rows);
	ASSERT(yCoor < m_cols);
	sf::Vector2f position;

	// Calculate Hexagon position based on array position
	position.x = 60*xCoor;
	position.y = 31*yCoor;

	// Offset every other row to tessellate hexagons
	if (0 == yCoor%2) {
		position.x += 30;
	}

	// Offset Hexagons from edge of screen
	position.x += 40;
	position.y += 40;

	return position;
}

sf::Vector2i Map::positionToCoordinates(
	sf::Vector2f position
	) {
	// Determine the coordinates by applying the opposite procedure to calculating the positions
	double xTmp = position.x - 40.0;
	double yTmp = position.y - 40.0;

	yTmp /= 31.0;

	double fMod2 = fmod(yTmp,2.0);
	if ((-0.5 < fMod2)&&(fMod2 < 0.5)) {
		xTmp -= 30;
	}

	xTmp /= 60;

	sf::Vector2i coors;
	coors.x = (int) std::round(xTmp);
	coors.y = (int) std::round(yTmp);

	// Correct for bug where tile right of correct tile is selected
	sf::Vector2f tilePos = getTile(coors)->getPosition();
	if ((position.x < tilePos.x - 31)&&(0 < coors.x)) {
		coors.x -= 1;
	}

	return coors;
}

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
