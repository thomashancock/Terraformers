#ifndef ENTITY_H
#define ENTITY_H

// STD
#include <vector>
#include <memory>

// LOCAL
#include "Component.hpp"

class Entity {
	using componentList = std::vector< std::shared_ptr<Component> >;

public:
	//! Entity constructor
	Entity();

	//! Returns the id of the entity
	int getID() const { return m_id; }

private:
	static int s_idGenerator; //!< Generates a unique id for the entity

	const int m_id; //!< The Entities ID

	componentList m_components; //!< List of components
};

#endif /* ENTITY_H */
