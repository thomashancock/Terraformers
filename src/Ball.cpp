#include "Ball.hpp"

// Public:
Ball::Ball(
	Type type
	) : 
	m_type(type)
	{
	m_sprite.setRadius(10);
	m_sprite.setFillColor(sf::Color::Black);
	
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
}

void Ball::drawCurrent(
	sf::RenderTarget& target,
	sf::RenderStates states
) const {
	target.draw(m_sprite, states);
}

float Ball::getRadius() {
	return m_sprite.getRadius();
}

// Private:
unsigned int Ball::getCategory() const {
	return Category::Tile;
}