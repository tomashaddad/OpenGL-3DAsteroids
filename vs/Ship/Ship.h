#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"
#include "Collisions/Collidable.h"

enum class Axis {
	x,
	y,
	z
};

enum class Direction {
	forward,
	backward
};

class Ship : public Collidable {
public:
	Ship();
	Ship(float x, float y, float z);
	Ship(Vector3D position);

	void draw() const;

	void move(Direction direction, float dt);
	void rotate(const Axis axis, const float angle);

	const Vector3D& getPosition() const;
	const Quaternion& getRotation() const;

	void reset();

	bool collidesWith(Collidable &other, Type type) override;
	void handleCollision(Collidable &other, Type type) override;
	void reactToCollision(Collidable &other, Type type) override;

private:
	Vector3D position;
	Quaternion rotation;
};

#endif // I3D_SHIP_H