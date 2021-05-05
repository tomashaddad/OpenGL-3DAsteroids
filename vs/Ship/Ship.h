#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

enum class Axis {
	x,
	y,
	z
};

enum class Direction {
	positive,
	negative
};

class Ship {
public:
	Ship();
	Ship(float x, float y, float z);
	Ship(Vector3D position);

	void draw() const;

	void rotate(const Axis movement, const Direction direction, const float dt);

	void yaw(float angle, float dt);
	void pitch(float angle, float dt);
	void roll(float angle, float dt);

	const Vector3D& getPosition() const;
	const Quaternion& getRotation() const;

	void reset();

private:
	Vector3D position;
	Quaternion rotation;
};

#endif // I3D_SHIP_H