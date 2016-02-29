#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category {
	enum Type {
		None = 0,
		Scene = 1 << 0,
		Tile = 1 << 1,
		LeftPaddle = 1 << 2,
		RightPaddle = 1 << 3,
	};
}

#endif /* CATEGORY_HPP */