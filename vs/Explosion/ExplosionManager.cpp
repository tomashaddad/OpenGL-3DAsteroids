#include "ExplosionManager.h"

#include "Math/Utility.h"
#include "Transparent/Transparent.h"
#include <algorithm>

#include <iostream>

void ExplosionManager::populate(const Vector3D& position) {
	// Generate velocities such that they are perpendicular to where the camera is currently facing
	for (int i = 0; i < EXPLOSION_NUMBER; ++i) {
		Vector3D velocity = utility::randFloat(EXPLOSION_MIN_VELOCITY, EXPLOSION_MAX_VELOCITY) * Vector3D::randomUnit();
		addExplosion(position, velocity);
	}
}

void ExplosionManager::addExplosion(Vector3D position, Vector3D velocity) {
	std::shared_ptr<Explosion> explosion = std::make_shared<Explosion>(position, velocity);
	explosions.emplace_back(explosion);
	Transparent::add(explosion);
}

void ExplosionManager::updateExplosions(float dt) {
	for (auto i = 0; i < explosions.size(); ++i) {
		explosions[i]->update(dt);

		if (explosions[i]->markedForDeletion()) {
			Transparent::remove(explosions[i]);
			deleteExplosionByIndex(i);
		}
	}
}

void ExplosionManager::deleteExplosionByIndex(unsigned int index) {
	std::swap(explosions[index], explosions.back());
	explosions.pop_back();
}

std::vector<std::shared_ptr<Explosion>>& ExplosionManager::getExplosions() { return explosions; }

void ExplosionManager::clearExplosions() {
	explosions.clear();
}