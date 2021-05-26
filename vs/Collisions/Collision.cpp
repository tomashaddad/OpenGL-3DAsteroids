#define _USE_MATH_DEFINES
#include <cmath>

#include "Collision.h"
#include "Enums/Enum.h"
#include "Constants/ArenaConstants.h"

bool collision::withWall(const Wall& wall, const Vector3D& position, float radius) {
	bool collision = false;
	if (wall.getSide() == Side::TOP) {
		collision = position.Y + radius > ARENA_DIM;
	}
	else if (wall.getSide() == Side::BOTTOM) {
		collision = position.Y - radius < -ARENA_DIM;
	}
	else if (wall.getSide() == Side::LEFT) {
		collision = position.X - radius < -ARENA_DIM;
	}
	else if (wall.getSide() == Side::RIGHT) {
		collision = position.X + radius > ARENA_DIM;
	}
	else if (wall.getSide() == Side::FRONT) {
		collision = position.Z + radius > ARENA_DIM;
	}
	else if (wall.getSide() == Side::BACK) {
		collision = position.Z - radius < -ARENA_DIM;
	}
	return collision;
}

void collision::resolve(const Wall& wall, Asteroid& asteroid) {
	if (wall.getSide() == Side::TOP || wall.getSide() == Side::BOTTOM) {
		asteroid.reverseY();
	}
	else if (wall.getSide() == Side::LEFT || wall.getSide() == Side::RIGHT) {
		asteroid.reverseX();
	}
	else if (wall.getSide() == Side::FRONT || wall.getSide() == Side::BACK) {
		asteroid.reverseZ();
	}
}

bool collision::withAsteroid(const Vector3D& p1, const Vector3D& p2, float r1, float r2) {
	return Vector3D::distance(p1, p2) < r1 + r2;
}

void collision::resolve(Asteroid& a1, Asteroid& a2) {
	Vector3D x1 = a1.getPosition();
	Vector3D x2 = a2.getPosition();
	Vector3D v1 = a1.getVelocity();
	Vector3D v2 = a2.getVelocity();
	float m1 = a1.getMass();
	float m2 = a2.getMass();
	float distance = Vector3D::distance(a1.getPosition(), a2.getPosition());
	float squared_distance = distance * distance;

	Vector3D new_v1 = v1 - ((2 * m2 / (m1 + m2)) * (Vector3D::dot(v1 - v2, x1 - x2) / squared_distance) * (x1 - x2));
	Vector3D new_v2 = v2 - ((2 * m1 / (m1 + m2)) * (Vector3D::dot(v2 - v1, x2 - x1) / squared_distance) * (x2 - x1));

	a1.setVelocity(new_v1);
	a2.setVelocity(new_v2);
}
