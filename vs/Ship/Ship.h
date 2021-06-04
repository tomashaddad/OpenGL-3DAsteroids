#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Constants/ShipConstants.h"

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

#include "Arena/Wall.h"

#include <vector>

#include "Model/Triangle.h"
#include "Model/Model.h"
#include "Model/Material.h"

#include "Bullets/BulletStream.h"

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

	void update(const float dt);
	void draw() const;
	void updateBullets(const float dt);

	void move(Direction direction, float dt);
	void setAccelerationToZero();
	void roll(const Axis axis, const float dt);
	void rotate(const Axis axis, const float dt, const float map, const float speed = MOUSE_ROTATION_SPEED);
	void shoot(float dt);

	std::vector<std::shared_ptr<Bullet>>& getBullets();
	const Vector3D& getPosition() const;
	const Quaternion& getRotation() const;
	const float& getWarningRadius() const;
	const float& getCollisionRadius() const;

	void reset();

private:
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	Quaternion rotation;

	BulletStream bullet_stream;

	float warning_radius;
	float collision_radius;
	float fire_timer;
	float fire_rate;

	unsigned int logo;
	std::vector<Vector3D> vertices;
	std::vector<Vector3D> uvs;
	std::vector<Vector3D> normals;
	std::vector<Triangle> triangles;
	std::vector<Material> materials;
};

#endif // I3D_SHIP_H