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