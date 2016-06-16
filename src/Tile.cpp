#include "Tile.hpp"

// Public:
Tile::Tile(
	Type type,
	int xPos,
	int yPos
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
	resetColor();

	// Set Tile Origin
	m_sprite.setOrigin(0, 0);

	// Set Tile position to the passed coordinates
	this->setPosition(xPos,yPos);

	isSelected = false;
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
	resetColor();
}

void Tile::select() {
	if (Type::Border != m_type) {
		isSelected = true;
	}
	resetColor();
}

void Tile::deselect() {
	isSelected = false;
	resetColor();
}

sf::Vector2f Tile::getTilePosition() {
	return this->getPosition();
}

// Private:
unsigned int Tile::getCategory() const {
	return Category::Tile;
}

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

	if (true == isSelected) {
		m_sprite.setOutlineThickness(2);
		m_sprite.setOutlineColor(sf::Color::Yellow);
	} else {
		m_sprite.setOutlineThickness(0);
		m_sprite.setOutlineColor(sf::Color::Transparent);
	}
}
