#ifndef TILE_H
#define TILE_H

// SFML
#include <SFML/Graphics.hpp>

// LOCAL
#include "SceneNode.hpp"
// #include "Unit.hpp"

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
		sf::Vector2i coors,
		sf::Vector2f pos
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

private:
	void resetColor();

private:
	Type m_type;

	const sf::Vector2i m_coors;

	sf::ConvexShape m_sprite;
	sf::ConvexShape m_borderSprite;

	bool m_isHighlighted = false;
	bool m_isSelected = false;

	sf::Font m_debugFont;
};

#endif /* TILE_H */
