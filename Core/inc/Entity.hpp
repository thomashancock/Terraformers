#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
	Entity();

	int getID() const { return m_id; }

private:
	static int s_idGenerator;

	const int m_id;
};

#endif /* ENTITY_H */
