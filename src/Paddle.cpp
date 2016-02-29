#include "Paddle.hpp"

// Public:
Paddle::Paddle(
	Type type
	) : 
	m_type(type)
	{
	m_sprite.setSize(sf::Vector2f(10,PADDLE_HEIGHT));
	
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);

	sf::Color paddleColour;
	switch (m_type) {
		case Type::Player1:
			paddleColour = sf::Color::Red;
			break;
		case Type::Player2:
			paddleColour = sf::Color::Blue;
			break;
		default:
			paddleColour = sf::Color::Green;
	}
	m_sprite.setFillColor(paddleColour);
}

void Paddle::drawCurrent(
	sf::RenderTarget& target,
	sf::RenderStates states
) const {
	target.draw(m_sprite, states);
}

float Paddle::getHeight() {
	return (float) PADDLE_HEIGHT;
}

// Private:
unsigned int Paddle::getCategory() const {
	switch (m_type) {
		case Player1:
			return Category::RightPaddle;

		default:
			return Category::LeftPaddle;
	}
}