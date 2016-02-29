#include "SceneNode.hpp"

// Public:
SceneNode::SceneNode()
: m_children()
, m_parent(nullptr)
{
}

void SceneNode::attachChild(Ptr child) {
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(
	const SceneNode& node
	) {
	auto found = std::find_if(m_children.begin(), m_children.end(), 
		[&] (Ptr& p)->bool {
			return p.get() == &node;
		}
	);

	assert(found != m_children.end());

	Ptr result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void SceneNode::update(
	sf::Time dt
	) {
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::onCommand(
	const Command& command,
	sf::Time dt
	) {
	if (command.category & getCategory()) {
		command.action(*this, dt);
	}

	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr) {
		(*itr)->onCommand(command, dt);
	}
}

unsigned int SceneNode::getCategory() const {
	return Category::Scene;
}

// Private:

void SceneNode::draw(
	sf::RenderTarget& target, 
	sf::RenderStates states
	) const {
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(
	sf::RenderTarget&, 
	sf::RenderStates
	) const {
	// Do nothing by default
}

void SceneNode::drawChildren(
	sf::RenderTarget& target, 
	sf::RenderStates states
	) const {
	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr) {
		(*itr)->draw(target, states);
	}
}

void SceneNode::updateCurrent(
	sf::Time
	) {
}

void SceneNode::updateChildren(
	sf::Time dt
	) {
	for (const Ptr& child : m_children) {
		child->update(dt);
	}
}