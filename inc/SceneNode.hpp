#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>

#include "Command.hpp"
#include "Category.hpp"

class SceneNode :
	public sf::Transformable,
	public sf::Drawable,
	private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;

	public: 
		SceneNode();
		
		void attachChild(
			Ptr child
		);
		
		Ptr detachChild(
			const SceneNode& node
		);
		
		void update(
			sf::Time dt
		);

		void onCommand(
			const Command& command,
			sf::Time dt
		);

		virtual unsigned int getCategory() const;

	private:
		virtual void draw(
			sf::RenderTarget& target,
			sf::RenderStates states
		) const;

		virtual void drawCurrent(
			sf::RenderTarget& target,
			sf::RenderStates states
		) const;

		virtual void drawChildren(
			sf::RenderTarget& target, 
			sf::RenderStates states
		) const;

		virtual void updateCurrent(sf::Time dt);
		void updateChildren(sf::Time dt);

	private:
		std::vector<Ptr> m_children;
		SceneNode*	m_parent;
};

#endif /* SCENENODE_H */