#include "Tile.hpp"

// STD
#include <cmath>
#include <sstream>

// LOCAL
#include "Debug.hpp"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Public:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Tile::Tile(
	Type type,
	sf::Vector2i coors,
	sf::Vector2f pos
) :
	m_type(type),
	m_coors(coors)
{
	if (!m_debugFont.loadFromFile("../Fonts/Arial.ttf")) {
		STD_ERR("Unable to load font");
		ASSERT(false);
	}

	const float sideLength = 36.0;

	// Create Hexagon Sprites
	auto setSpriteShape = [&sideLength] (
		sf::ConvexShape& sprite
	) {
		const static float sqrt3 = std::sqrt(3.0);
		sprite.setPointCount(6);
		sprite.setPoint(0, sf::Vector2f( 0, sideLength ) );
		sprite.setPoint(1, sf::Vector2f( sqrt3*sideLength/2.0,  sideLength/2.0) );
		sprite.setPoint(2, sf::Vector2f( sqrt3*sideLength/2.0, -sideLength/2.0) );
		sprite.setPoint(3, sf::Vector2f( 0, -sideLength ) );
		sprite.setPoint(4, sf::Vector2f( -sqrt3*sideLength/2.0, -sideLength/2.0) );
		sprite.setPoint(5, sf::Vector2f( -sqrt3*sideLength/2.0,  sideLength/2.0) );

		sprite.setOrigin(0, 0);
	};

	// Setup tile sprite
	setSpriteShape(m_sprite);
	m_sprite.setOutlineThickness(2);
	m_sprite.setOutlineColor(sf::Color::White);

	// Setup Border overlay
	setSpriteShape(m_borderSprite);
	m_borderSprite.setOutlineThickness(2);
	m_borderSprite.setFillColor(sf::Color(0,0,0,0));

	// Set Colour based on the passed tile type
	resetColor();

	// Set Tile position to the passed coordinates
	this->setPosition(pos.x,pos.y);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Tile::drawCurrent(
	sf::RenderTarget& target,
	sf::RenderStates states
) const {
	target.draw(m_sprite, states);
	target.draw(m_borderSprite, states);

	// For Debugging
	std::stringstream printCoor;
	printCoor << m_coors.x << " " << m_coors.y << " " << 0 - m_coors.x - m_coors.y;
	sf::Text location(printCoor.str(),m_debugFont,10);
	auto position = this->getPosition();
	position.x -= 20;
	position.y -= 10;
	location.setPosition(position);
	target.draw(location);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Tile::setType(
	Type type
) {
	m_type = type;
	resetColor();
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Tile::highlight() {
	if (Type::Border != m_type) {
		if (false == m_isSelected) {
			m_isHighlighted = true;
		}
	}
	resetColor();
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Tile::unhighlight() {
	m_isHighlighted = false;
	resetColor();
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Tile::select() {
	if (Type::Border != m_type) {
		m_isSelected = true;
	}
	resetColor();
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Tile::deselect() {
	m_isSelected = false;
	resetColor();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Private:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Tile::resetColor() {
	if (Type::Border == m_type) {
		m_sprite.setFillColor(sf::Color::Black);
	} else if (Type::Forest == m_type) {
		m_sprite.setFillColor(sf::Color::Green);
	} else if (Type::Mountain == m_type) {
		m_sprite.setFillColor(sf::Color::Red);
	} else {
		sf::Color gray(125,125,125);
		m_sprite.setFillColor(gray);
	}

	if (true == m_isSelected) {
		m_borderSprite.setOutlineColor(sf::Color::Blue);
	} else if (true == m_isHighlighted) {
		m_borderSprite.setOutlineColor(sf::Color::Yellow);
	} else {
		m_borderSprite.setOutlineColor(sf::Color::White);
	}
}
