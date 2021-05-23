#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

#include "Arena/Wall.h"

#include <vector>

#include "Model/Triangle.h"

#include "Model/Model.h"

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

	void loadModel(std::string filename);

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

	std::vector<Triangle> triangles;
	std::vector<Vector3D> vertices;
	std::vector<Vector3D> normals;
};

#endif // I3D_SHIP_H