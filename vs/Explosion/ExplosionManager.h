#ifndef I3D_EXPLOSIONMANAGER_H
#define I3D_EXPLOSIONMANAGER_H

#include "Math/Vector3D.h"
#include "Explosion.h"

#include <vector>

class ExplosionManager {
public:
	ExplosionManager();
	void populate(const Vector3D& asteroid_position);
	void addExplosion(Vector3D position, Vector3D velocity);
	void updateExplosions(float dt);
	void deleteExplosionByIndex(unsigned int index);
	void clearExplosions();

	std::vector<std::shared_ptr<Explosion>>& getExplosions();

private:
	std::vector<std::shared_ptr<Explosion>> explosions;
};

#endif