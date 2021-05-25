#ifndef I3D_ENUM_H
#define I3D_ENUM_H

enum class Side {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	FRONT,
	BACK,
};

enum class CollisionType {
	WARNING,
	COLLISION
};

enum class Look {
	ABOVE,
	BELOW,
	LEFT,
	RIGHT,
	AHEAD,
	BEHIND,
};

#endif