#include "Map.hpp"

// Public:
Map::Map(
	int rows,
	int cols
	) {
	m_rows = rows;
	m_cols = cols;

	for (int i = 0; i < m_rows; i++) {
		std::vector<Tile*> mapRow;
		for (int j = 0; j < m_cols; j++) {
			// Create unique pointer to the tile
			std::unique_ptr<Tile> tile(new Tile(Tile::Basic,0,0));
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

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (0 == j%2) {
				m_tileMap.at(i).at(j)->setType(Tile::Mountain);
			}
		}
	}

	setTilePositions();
}

// Private:
unsigned int Map::getCategory() const {
	return Category::Tile;
}

void Map::setTilePositions() {
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			// Calculate Hexagon position based on array position
			int xCoor = 60*i;
			int yCoor = 52*j;
			if (0 == j%2) {
				// Offset every other row to teselate hexagons
				xCoor += 30;
			}

			// Offset Hexagons from edge of screen
			xCoor += 40;
			yCoor += 40;

			m_tileMap.at(i).at(j)->setPosition(xCoor,yCoor);
		}
	}
}