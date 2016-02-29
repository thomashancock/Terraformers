#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include "./SceneNode.hpp"

class Entity :
public SceneNode 
{
	public:
		void setVelocity(
			sf::Vector2f velocity
		);
		
		void setVelocity(
			float vx, 
			float vy
		);

		void accelerate(
			sf::Vector2f velocity
		);

		void accelerate(
			float vx,
			float vy
		);
		
		sf::Vector2f getVelocity() const;

		virtual void updateCurrent(
			sf::Time dt
		);

	private:
		sf::Vector2f m_velocity;
};


#endif /* ENTITY_H */