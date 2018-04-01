#include "TileBank.hpp"

// LOCAL
#include "Debug.hpp"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Public:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
TileBank::TileBank() {
	STD_LOG("Tile Bank Constructor");
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void TileBank::addTile(
	const sf::Vector2i coors,
	const sf::Vector2f position
) {
	ASSERT(m_tiles.find(coors) == m_tiles.end());

	// Create unique pointer to the tile
	std::unique_ptr<Tile> tile(new Tile(Tile::Basic,coors,position));

	// Copy the unique pointer to a regular pointer
	Tile* tilePtr = tile.get();

	// Attach unique pointer as sceneNode child
	this->attachChild(std::move(tile));

	// Store regular pointer in tile map
	m_tiles.insert(std::make_pair(coors,tilePtr));
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Tile* TileBank::getTile(
	sf::Vector2i coors
) const {
	auto search = m_tiles.find(coors);
	if (search != m_tiles.end()) {
		return search->second;
	}	else {
		return nullptr;
	}
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void TileBank::unhighlightAll() {
	for (auto& entry : m_tiles) {
		entry.second->unhighlight();
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Private:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
