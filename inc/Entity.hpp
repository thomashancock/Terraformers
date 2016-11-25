#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include "./SceneNode.hpp"

class Entity :
public SceneNode 
{
	public:
		void setCoors(
			sf::Vector2i coors
		);
		
		void setCoors(
			int xCoor, 
			int yCoor
		);
		
		sf::Vector2i getCoors() const;

		virtual void updateCurrent(
			sf::Time dt
		);

	private:
		sf::Vector2i m_mapCoors;
};


#endif /* ENTITY_H */