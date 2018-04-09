#ifndef SYSTEM_H
#define SYSTEM_H

class System {
public:
	//! System Constructor
	System();

	//! Delete copy constructor
	System(const System&) = delete;
	//! Delete copy assignment operator
	System& operator=(const System&) = delete;
	//! Delete Move constructor
	System(System&& rhs) = delete;
	//! Delete move assignment operator
	System& operator=(System&& rhs) = delete;

	//! Pure virtual function for updating system components
	virtual void update() = 0;

private:

private:

};

#endif /* SYSTEM_H */
