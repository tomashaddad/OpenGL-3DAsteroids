#define _USE_MATH_DEFINES
#include <cmath>

#include "Collision.h"
#include "Enums/Enum.h"
#include "Constants/ArenaConstants.h"

bool Collision::shipWithWall(std::unique_ptr<Ship>& ship, std::unique_ptr<Wall>& wall, CollisionType type) {
	float radius = type == CollisionType::WARNING ? ship->getWarningRadius() : ship->getCollisionRadius();
	bool collision = false;
	if (wall->getSide() == Side::TOP) {
		collision = ship->getPosition().Y + radius > ARENA_DIM;
	}
	else if (wall->getSide() == Side::BOTTOM) {
		collision = ship->getPosition().Y - radius < -ARENA_DIM;
	}
	else if (wall->getSide() == Side::LEFT) {
		collision = ship->getPosition().X - radius < -ARENA_DIM;
	}
	else if (wall->getSide() == Side::RIGHT) {
		collision = ship->getPosition().X + radius > ARENA_DIM;
	}
	else if (wall->getSide() == Side::FRONT) {
		collision = ship->getPosition().Z + radius > ARENA_DIM;
	}
	else if (wall->getSide() == Side::BACK) {
		collision = ship->getPosition().Z - radius < -ARENA_DIM;
	}

	return collision;
}