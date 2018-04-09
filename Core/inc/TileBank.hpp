#ifndef TILEBANK_H
#define TILEBANK_H

// STD
#include <map>

// SFML
#include <SFML/System.hpp>

// LOCAL
#include "SceneNode.hpp"
#include "Tile.hpp"

class TileBank :
public SceneNode
{
public:
	TileBank();

	void addTile(
		const sf::Vector2i coors,
		const sf::Vector2f position
	);

	Tile* getTile(
		const sf::Vector2i coors
	) const;

	void unhighlightAll();

private:

private:
	// Comparitor for Vector2i to facilitate map storage
	struct compareVector2i {
		bool operator() (
			const sf::Vector2i& a,
			const sf::Vector2i& b
		) const {
			if (a.x != b.x) {
				return a.x < b.x;
			} else {
				return a.y < b.y;
			}
		}
	};

	std::map< sf::Vector2i, Tile*, compareVector2i > m_tiles;
};

#endif /* TILEBANK_H */
