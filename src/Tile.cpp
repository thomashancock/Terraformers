#include "Tile.hpp"

// Public:
Tile::Tile(
	Type type,
	int xCoor,
	int yCoor
	) :
	m_type(type)
	{
	// Create Hexagon Sprite
	m_sprite.setPointCount(6);
	const int hexagonWidth = 29;
	m_sprite.setPoint(0, sf::Vector2f(0, -20));
	m_sprite.setPoint(1, sf::Vector2f(hexagonWidth, -10));
	m_sprite.setPoint(2, sf::Vector2f(hexagonWidth, 10));
	m_sprite.setPoint(3, sf::Vector2f(0, 20));
	m_sprite.setPoint(4, sf::Vector2f(-1*hexagonWidth, 10));
	m_sprite.setPoint(5, sf::Vector2f(-1*hexagonWidth, -10));

	// Set Colour based on the passed tile type
	resetColour();

	// Set Tile Origin
	m_sprite.setOrigin(0, 0);

	// Set Tile position to the passed coordinates
	this->setPosition(xCoor,yCoor);
}

void Tile::drawCurrent(
	sf::RenderTarget& target,
	sf::RenderStates states
	) const {
	target.draw(m_sprite, states);
}

void Tile::setType(
	Type type
	) {
	m_type = type;
	resetColour();
}

// Private:
unsigned int Tile::getCategory() const {
	return Category::Tile;
}

void Tile::resetColour() {
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
}
