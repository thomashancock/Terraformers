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
	std::unique_ptr<Map> map(new Map(10,10));
	m_map = map.get();
	m_sceneLayers[Background]->attachChild(std::move(map));

	// // Add Ball:
	// std::unique_ptr<Ball> ball(new Ball(Ball::Basic));
	// m_ball = ball.get();
	// m_ball->setPosition(m_window.getSize().x/2.f, m_window.getSize().y/2.f);
	// m_ball->setVelocity(60.f,100.f);
	// m_sceneLayers[Front]->attachChild(std::move(ball));

	// // Add Player Paddle:
	// std::unique_ptr<Paddle> paddlePlayer(new Paddle(Paddle::Player1));
	// m_playerPaddle = paddlePlayer.get();
	// m_playerPaddle->setPosition(m_window.getSize().x - 30, m_window.getSize().y/2.f);
	// m_playerPaddle->setVelocity(0.f,0.f);
	// m_sceneLayers[Front]->attachChild(std::move(paddlePlayer));

	// // Add AI Paddle:
	// std::unique_ptr<Paddle> paddleAI(new Paddle(Paddle::AI));
	// m_AIPaddle = paddleAI.get();
	// m_AIPaddle->setPosition(30, m_window.getSize().y/2.f);
	// m_AIPaddle->setVelocity(0.f,0.f);
	// m_sceneLayers[Front]->attachChild(std::move(paddleAI));
}
