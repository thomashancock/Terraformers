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

	void select();
	void deselect();

private:
	virtual unsigned int getCategory() const;

	void resetColor();
	bool isMouseOnTile();

private:
	Type m_type;
	sf::ConvexShape m_sprite;
	bool isSelected;
};

#endif /* TILE_H */
