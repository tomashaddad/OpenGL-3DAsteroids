#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

#include "Arena/Wall.h"

enum class Axis {
	x,
	y,
	z
};

enum class Direction {
	forward,
	backward
};

class Ship {
public:
	Ship();
	Ship(float x, float y, float z);
	Ship(Vector3D position);

	void draw() const;

	void move(Direction direction, float dt);
	void rotate(const Axis axis, const float angle);

	const Vector3D& getPosition() const;
	const Quaternion& getRotation() const;
	const float& getWarningRadius() const;
	const float& getCollisionRadius() const;

	void reset();

private:
	Vector3D position;
	Quaternion rotation;

	float warning_radius;
	float collision_radius;
};

#endif // I3D_SHIP_H