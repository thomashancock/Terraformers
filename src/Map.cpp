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
}

sf::Vector2f Map::coorsToPosition(
	int xCoor,
	int yCoor
	) {
	ASSERT(xCoor < m_rows);
	ASSERT(yCoor < m_cols);
	return getTile(xCoor,yCoor)->getPosition();
}

Tile* Map::getTile(
	int xCoor,
	int yCoor
) {
	ASSERT(xCoor < m_rows);
	ASSERT(yCoor < m_cols);
	return 	m_tileMap.at(xCoor).at(yCoor);
}

Tile* Map::getTileAtPosition(
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

	int xCoor = (int) std::round(xTmp);
	int yCoor = (int) std::round(yTmp);

	// Ensure Tile coordinates are valid
	if ((-1 < xCoor)&&(xCoor < m_rows)&&(-1 < yCoor)&&(yCoor < m_cols)) {
		// Correct for bug where tile right of correct tile is selected
		sf::Vector2f tilePos = getTile(xCoor,yCoor)->getTilePosition();
		if ((position.x < tilePos.x - 31)&&(0 < xCoor)) {
			xCoor -= 1;
		}

		return getTile(xCoor,yCoor);
	} else {
		return NULL;
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
