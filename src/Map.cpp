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
	return m_tileMap.at(xCoor).at(yCoor)->getPosition();
}

// Private:
sf::Vector2f Map::setTilePosition(
	int xCoor,
	int yCoor
	) {
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

unsigned int Map::getCategory() const {
	return Category::Tile;
}

void Map::setupMap() {
	STD_LOG("Populating Map");
	for (int i = 0; i < m_rows; i++) {
		m_tileMap.at(i).at(0)->setType(Tile::Border);
		m_tileMap.at(i).at(m_cols-1)->setType(Tile::Border);
	}
	for (int j = 1; j < m_cols-1; j++) {
		m_tileMap.at(0).at(j)->setType(Tile::Border);
		m_tileMap.at(m_rows-1).at(j)->setType(Tile::Border);
	}

	// Randomly define Forest and Mountain
	int randRow = (rand()%(m_rows-4))+2;
	int randCol = (rand()%(m_cols-4))+2;
	ASSERT(randRow < m_rows);
	ASSERT(randCol < m_cols);
	m_tileMap.at(randRow).at(randCol)->setType(Tile::Forest);

	randRow = (rand()%(m_rows-4))+2;
	randCol = (rand()%(m_cols-4))+2;
	ASSERT(randRow < m_rows);
	ASSERT(randCol < m_cols);
	m_tileMap.at(randRow).at(randCol)->setType(Tile::Mountain);
}
