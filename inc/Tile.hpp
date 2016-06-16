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
		int xPos,
		int yPos
	);

	virtual void drawCurrent(
		sf::RenderTarget& target,
		sf::RenderStates states
	) const;

	void setType(
		Type type
	);

	void highlight();
	void unhighlight();
	void select();
	void deselect();

	sf::Vector2f getTilePosition();

private:
	virtual unsigned int getCategory() const;

	void resetColor();

private:
	Type m_type;
	sf::ConvexShape m_sprite;
	bool m_isHighlighted;
	bool m_isSelected;
};

#endif /* TILE_H */
