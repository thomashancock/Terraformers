#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "./SceneNode.hpp"
#include "./Unit.hpp"

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

	bool attachUnit(
		Unit* unit
	);
	void detatchUnit();
	Unit* getUnit();
	bool hasPlacedUnit();

private:
	void resetColor();

private:
	Type m_type;
	sf::ConvexShape m_sprite;
	bool m_isHighlighted;
	bool m_isSelected;

	Unit* m_placedUnit;
};

#endif /* TILE_H */
