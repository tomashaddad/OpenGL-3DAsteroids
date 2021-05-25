#ifndef I3D_COLLISION_H
#define I3D_COLLISION_H

#include "Ship/Ship.h"
#include "Asteroids/Asteroid.h"
#include "Arena/Wall.h"

#include <memory>

namespace collision {
	bool withWall(const Wall& wall, const Vector3D& position, float radius = 0);

	void resolve(const Wall& wall, Asteroid& asteroid);
}

#endif