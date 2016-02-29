#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H

namespace sf {
	class Texture;
}

namespace Textures {
	enum ID {
		Basic,
		Small,
	};
}

template <typename Resource, typename Identifier> class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif /* RESOURCEIDENTIFIERS_H */