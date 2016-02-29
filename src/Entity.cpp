#include "Entity.hpp"

void Entity::setVelocity(
	sf::Vector2f velocity
	) {
	m_velocity = velocity;
}

void Entity::setVelocity(
	float vx, 
	float vy
	) {
	m_velocity.x = vx;
	m_velocity.y = vy;
}

void Entity::accelerate(
	sf::Vector2f velocity
	) {
	m_velocity += velocity;
}

void Entity::accelerate(
	float vx,
	float vy
	) {
	m_velocity.x += vx;
	m_velocity.y += vy;
}

sf::Vector2f Entity::getVelocity() const {
	return m_velocity;
}

void Entity::updateCurrent(
	sf::Time dt
	) {
	move(m_velocity * dt.asSeconds());
}