#include "Tile.hpp"

// STD
#include <cmath>

// LOCAL
#include "Debug.hpp"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Public:
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Tile::Tile(
	Type type,
	float xPos,
	float yPos
) :
	m_type(type)
{
	// Create Hexagon Sprites
	m_sprite.setPointCount(6);
	// const int hexagonHeight = 30;
	// const int hexagonWidth = 36;
	const float sideLength = 36.0;
	const static float sqrt3 = std::sqrt(3.0);
	m_sprite.setPoint(0, sf::Vector2f( 0, sideLength ) );
	m_sprite.setPoint(1, sf::Vector2f( sqrt3*sideLength/2.0,  sideLength/2.0) );
	m_sprite.setPoint(2, sf::Vector2f( sqrt3*sideLength/2.0, -sideLength/2.0) );
	m_sprite.setPoint(3, sf::Vector2f( 0, -sideLength ) );
	m_sprite.setPoint(4, sf::Vector2f( -sqrt3*sideLength/2.0, -sideLength/2.0) );
	m_sprite.setPoint(5, sf::Vector2f( -sqrt3*sideLength/2.0,  sideLength/2.0) );


	// Set Colour based on the passed tile type
	resetColor();

	// Set Tile Origin
	m_sprite.setOrigin(0, 0);

	// Set Tile position to the passed coordinates
	this->setPosition(xPos,yPos);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Tile::drawCurrent(
	sf::RenderTarget& target,
	sf::RenderStates states
) const {
	target.draw(m_sprite, states);
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
//
// -----------------------------------------------------------------------------
bool Tile::attachUnit(
	Unit* unit
) {
	if (NULL == m_placedUnit) {
		m_placedUnit = unit;
		return true;
	} else {
		STD_LOG(__FILE__ << ": attachUnit: Failed to attach unit. m_placedUnit is not NULL");
		return false;
	}
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Tile::detatchUnit() {
	m_placedUnit = NULL;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Unit* Tile::getUnit() {
	return m_placedUnit;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Tile::hasPlacedUnit() {
	if (NULL == m_placedUnit) {
		return false;
	} else {
		return true;
	}
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
		m_sprite.setOutlineThickness(2);
		m_sprite.setOutlineColor(sf::Color::Blue);
	} else if (true == m_isHighlighted) {
		m_sprite.setOutlineThickness(2);
		m_sprite.setOutlineColor(sf::Color::Yellow);
	} else {
		m_sprite.setOutlineThickness(0);
		m_sprite.setOutlineColor(sf::Color::Blue);
	}
}
