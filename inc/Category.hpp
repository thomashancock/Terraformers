#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category {
	enum Type {
		None = 0,
		Scene = 1 << 0,
		Tile = 1 << 1,
		Terraformer = 1 << 2,
		Solider = 1 << 3,
	};
}

#endif /* CATEGORY_HPP */