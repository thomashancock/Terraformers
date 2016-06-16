#include "World.hpp"

// Public:
World::World(sf::RenderWindow& window)
: m_window(window)
, m_sceneGraph()
, m_sceneLayers()
{
	buildScene();
	m_activeTile = NULL;
}

void World::update(
	sf::Time elapsedTime
	) {
	processMousePosition(elapsedTime);

	// Send Commands to the Scene Graph
	while (!m_commandQueue.isEmpty()) {
		m_sceneGraph.onCommand(m_commandQueue.pop(), elapsedTime);
	}

	// Update the Scene Graph
	m_sceneGraph.update(elapsedTime);
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

void World::processMousePosition(
	sf::Time elapsedTime
	) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

	// Ensure mouse is inside window
	sf::Vector2u windowSize = m_window.getSize();
	if ((mousePos.x > 0)&&
			(mousePos.x < (int) windowSize.x)&&
			(mousePos.y > 0)&&
			(mousePos.y < (int) windowSize.y)) {

		// View Scrolling
		updateViewPosition(mousePos,elapsedTime);

		// Convert mouse position to world coordinates
		m_worldMousePos = m_window.mapPixelToCoords(mousePos);

		Tile* hoveredTile = m_map->getTileAtPosition(m_worldMousePos);
		if (m_activeTile != hoveredTile) {
			if (NULL != m_activeTile) {
				m_activeTile->unhighlight();
			}
			m_activeTile = hoveredTile;
			if (NULL != m_activeTile) {
				m_activeTile->highlight();
			}
		}
	}
}

void World::updateViewPosition(
	sf::Vector2i mousePos,
	sf::Time elapsedTime
	) {
	sf::Vector2u windowSize = m_window.getSize();

	sf::Vector2i scrollSpeed(0,0);

	// Set y scroll speed based on mouse position
	if (mousePos.y < (windowSize.y/10.0)) {
		scrollSpeed.y = -100;
	} else if (mousePos.y > (windowSize.y - (windowSize.y/10.0))) {
		scrollSpeed.y = 100;
	}

	// Set x scroll speed based on mouse position
	if (mousePos.x < (windowSize.x/10.0)) {
		scrollSpeed.x = -100;
	} else if (mousePos.x > (windowSize.x - (windowSize.x/10.0))) {
		scrollSpeed.x = 100;
	}

	// Update view using scroll speeds determined
	sf::View view = m_window.getView();
	view.move(scrollSpeed.x*elapsedTime.asSeconds(),scrollSpeed.y*elapsedTime.asSeconds());
	m_window.setView(view);
}
