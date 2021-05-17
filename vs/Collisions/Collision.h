#ifndef I3D_COLLISION_H
#define I3D_COLLISION_H

#include "Ship/Ship.h"
#include "Asteroids/Asteroid.h"
#include "Arena/Wall.h"

#include <memory>

namespace Collision {
	bool shipWithWall(std::unique_ptr<Ship>& ship, std::unique_ptr<Wall>& wall, CollisionType type);
}

#endif