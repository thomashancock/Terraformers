#include "World.hpp"

// Public:
World::World(sf::RenderWindow& window)
: m_window(window)
, m_sceneGraph()
, m_sceneLayers()
{
	buildScene();
}

void World::update(
	sf::Time dt
	) {
	// Send Commands to the Scene Graph
	while (!m_commandQueue.isEmpty()) {
		m_sceneGraph.onCommand(m_commandQueue.pop(), dt);
	}

	// Update the Scene Graph
	m_sceneGraph.update(dt);
}

void World::draw() {
	m_window.draw(m_sceneGraph);
}

CommandQueue& World::getCommandQueue() {
	return m_commandQueue;
}

// Private:
void World::buildScene() {
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		m_sceneLayers[i] = layer.get();

		m_sceneGraph.attachChild(std::move(layer));
	}

	// Draw the Hex grid map
	std::unique_ptr<Map> map(new Map(20,20));
	m_map = map.get();
	m_sceneLayers[Background]->attachChild(std::move(map));

	// Draw Unit
	std::unique_ptr<Unit> testUnit(new Unit(Unit::Basic));
	m_testUnit = testUnit.get();
	sf::Vector2f testUnitPos = m_map->coorsToPosition(5,3);
	m_testUnit->setPosition(testUnitPos.x,testUnitPos.y);
	m_sceneLayers[Front]->attachChild(std::move(testUnit));
}
