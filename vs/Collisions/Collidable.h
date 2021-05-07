#ifndef I3D_COLLISION_H
#define I3D_COLLISION_H

enum class Type {
	ship,
	wall,
	meteor,
	bullet
};

class Collidable {
	virtual bool collidesWith(Collidable &other, Type type) = 0;
	virtual void handleCollision(Collidable &other, Type type) = 0;
	virtual void reactToCollision(Collidable &other, Type type) = 0;
};

#endif // I3D_COLLISION_H