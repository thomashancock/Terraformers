#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
	//! Component Constructor
	Component();

	//! Delete copy constructor
	Component(const Component&) = delete;
	//! Delete copy assignment operator
	Component& operator=(const Component&) = delete;
	//! Delete Move constructor
	Component(Component&& rhs) = delete;
	//! Delete move assignment operator
	Component& operator=(Component&& rhs) = delete;


private:

};

#endif /* COMPONENT_H */
