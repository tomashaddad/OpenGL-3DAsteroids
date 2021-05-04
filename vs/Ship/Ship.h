#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

enum class Move {
	up,
	down,
	left,
	right,
	forward,
	backward
};

enum class Rotate {
	left,
	right
};

class Ship {
public:
	Ship();
	Ship(float x, float y, float z);
	Ship(Vector3D position);

	void draw() const;

	void move(const Move movement, const float dt);

	const Vector3D& getPosition() const;

private:
	Vector3D position;
	Quaternion rotation;
};

#endif // I3D_SHIP_H