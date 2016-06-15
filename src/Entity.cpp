#include "Entity.hpp"

void Entity::setCoors(
	sf::Vector2i coors
	) {
	m_mapCoors = coors;
}

void Entity::setCoors(
	int xCoor, 
	int yCoor
	) {
	m_mapCoors.x = xCoor;
	m_mapCoors.y = yCoor;
}

sf::Vector2i Entity::getCoors() const {
	return m_mapCoors;
}

void Entity::updateCurrent(
	sf::Time dt
	) {
	// Left blank in case useful later
}