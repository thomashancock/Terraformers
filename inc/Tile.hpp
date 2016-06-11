#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "./SceneNode.hpp"

class Tile :
public SceneNode
{
public:
	enum Type {
		Basic,
		Border,
		Forest,
		Mountain
	};

public:
	explicit Tile(
		Type type,
		int xCoor,
		int yCoor
	);

	virtual void drawCurrent(
		sf::RenderTarget& target,
		sf::RenderStates states
	) const;

	void setType(
		Type type
	);

private:
	virtual unsigned int getCategory() const;

	void resetColour();

private:
	Type m_type;
	sf::ConvexShape m_sprite;
	// sf::CircleShape m_sprite;
};

#endif /* TILE_H */
