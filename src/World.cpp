#include "World.hpp"

// Public:
World::World(sf::RenderWindow& window)
: m_window(window)
, m_sceneGraph()
, m_sceneLayers()
{
	buildScene();
	m_hoveredTile = NULL;
	m_selectedTile = NULL;

}

void World::update(
	sf::Time elapsedTime
	) {
	processMousePosition(elapsedTime);
	processMouseClicks(elapsedTime);

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
	m_map->placeUnit(testUnit.get(),5,3);
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
		if (m_hoveredTile != hoveredTile) {
			if (NULL != m_hoveredTile) {
				m_hoveredTile->unhighlight();
			}
			m_hoveredTile = hoveredTile;
			if (NULL != m_hoveredTile) {
				m_hoveredTile->highlight();
			}
		}
	}
}

void World::processMouseClicks(
	sf::Time elapsedTime
) {
	while (!m_commandQueue.isEmpty()) {
		Command command = m_commandQueue.pop();

		if (Input::Type::LeftMouse == command.getType()) {
			STD_LOG("Player Input: Left Mouse Button Pressed");
			if (NULL != m_hoveredTile) {
				if (NULL != m_selectedTile) {
					m_selectedTile->deselect();
				}
				m_selectedTile = m_hoveredTile;
				ASSERT(NULL != m_selectedTile);
				m_selectedTile->select();
			}
		}

		if (Input::Type::RightMouse == command.getType()) {
			STD_LOG("Player Input: Right Mouse Button Pressed");
		}

		if (Input::Type::Spacebar == command.getType()) {
			STD_LOG("Player Input: Spacebar Pressed");
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
