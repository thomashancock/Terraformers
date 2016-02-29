#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Ball :
public Entity
{
public:
	enum Type {
		Basic,
		Small,
	};

public:
	explicit Ball(
		Type type
	);
	
	virtual void drawCurrent(
		sf::RenderTarget& target,
		sf::RenderStates states
	) const;

	float getRadius();

private:
	virtual unsigned int getCategory() const;

private:
	Type m_type;
	sf::CircleShape m_sprite;
};

#endif /* BALL_H */