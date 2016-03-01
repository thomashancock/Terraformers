#include "Terraformer.hpp"

// Public:
Terraformer::Terraformer(
	Type type
	) : 
	m_type(type)
	{
	m_sprite.setSize(sf::Vector2f(20, 50));
	m_sprite.setFillColor(sf::Color::Yellow);
	
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width/2.f, bounds.height);
}

void Terraformer::drawCurrent(
	sf::RenderTarget& target,
	sf::RenderStates states
) const {
	target.draw(m_sprite, states);
}

// Private:
unsigned int Terraformer::getCategory() const {
	return Category::Terraformer;
}