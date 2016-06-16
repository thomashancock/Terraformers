#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

#include <queue>

#include "Command.hpp"
#include "SceneNode.hpp"

class CommandQueue
{
public:
	void push (
		const Command& command
	);

	Command pop();

	bool isEmpty() const;

private:
	std::queue<Command> m_queue;
};


#endif /* COMMANDQUEUE_HPP */
