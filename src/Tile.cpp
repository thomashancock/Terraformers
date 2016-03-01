#include "Tile.hpp"

// Public:
Tile::Tile(
	Type type,
	int xCoor,
	int yCoor
	) : 
	m_type(type)
	{
	m_sprite.setPointCount(6);
	m_sprite.setRadius(34);
	m_sprite.setScale(1,0.59);

	resetColour();
	
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);

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