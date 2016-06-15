#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Unit :
public Entity
{
public:
	enum Type {
		Basic
	};

public:
	explicit Unit(
		Type type
	);

	virtual void drawCurrent(
		sf::RenderTarget& target,
		sf::RenderStates states
	) const;

private:
	virtual unsigned int getCategory() const;

private:
	Type m_type;
	sf::RectangleShape m_sprite;
};

#endif /* UNIT_H */
