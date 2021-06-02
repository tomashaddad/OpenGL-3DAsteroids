#ifndef I3D_COLLISION_H
#define I3D_COLLISION_H

#include "Ship/Ship.h"
#include "Asteroids/Asteroid.h"
#include "Arena/Wall.h"

#include <memory>

namespace collision {
	bool withWall(const Wall& wall, const Vector3D& position, float radius = 0);
	void resolve(const Wall& wall, Asteroid& asteroid);

	bool withAsteroid(const Vector3D& asteroid_pos, float asteroid_radius, const Vector3D& other_position, float other_radius = 0);
	void resolve(Asteroid& a1, Asteroid& a2);
}

#endif