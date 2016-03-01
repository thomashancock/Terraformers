#ifndef TERRAFORMER_H
#define TERRAFORMER_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Terraformer :
public Entity
{
public:
	enum Type {
		Basic
	};

public:
	explicit Terraformer(
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

#endif /* TERRAFORMER_H */