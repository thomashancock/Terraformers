#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

#define PADDLE_HEIGHT (60)

class Paddle :
public Entity
{
public:
	enum Type {
		Player1,
		Player2,
		AI,
	};

public:
	explicit Paddle(
		Type type
	);
	
	virtual void drawCurrent(
		sf::RenderTarget& target,
		sf::RenderStates states
	) const;

	float getHeight();
	
private:
	virtual unsigned int getCategory() const;

private:
	Type m_type;
	sf::RectangleShape m_sprite;
};

#endif /* PADDLE_H */