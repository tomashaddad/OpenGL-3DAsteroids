#include "AsteroidField.h"
#include "Math/Utility.h"
#include "Constants/AsteroidConstants.h"
#include "Constants/ArenaConstants.h"

#include "Assets/Asset.h"
#include <algorithm>

AsteroidField::AsteroidField() :
	arena_radius(sqrt(3 * ARENA_DIM * ARENA_DIM)),
	asteroid_count(1),
	timer(0),
	time_between_levels(45),
	levelling_up(false) {
	textures.push_back(Asset::getTextureId(Entity::asteroid_1));
	textures.push_back(Asset::getTextureId(Entity::asteroid_2));
	textures.push_back(Asset::getTextureId(Entity::asteroid_3));
	textures.push_back(Asset::getTextureId(Entity::asteroid_4));
}

void AsteroidField::launchAsteroidsAtShip(Vector3D ship_position) {
	for (int i = 0; i < asteroid_count; ++i) {
		float speed = utility::randFloat(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
		Vector3D asteroid_position = Vector3D::randomUnit() * arena_radius;
		Vector3D asteroid_velocity = speed * Vector3D::normalise(ship_position - asteroid_position);
		asteroids.emplace_back(asteroid_position, asteroid_velocity, textures[utility::randInt(0, textures.size() - 1)]);
	}
	levelling_up = false;
}

void AsteroidField::updateAsteroids(float dt) {
	for (auto i = 0; i < asteroids.size(); ++i) {
		asteroids[i].update(dt);

		if (!asteroids[i].isInArena()) {
			asteroids[i].checkIfInArena(ARENA_DIM - 0.5);
		}

		if (asteroids[i].isMarkedForDeletion()) {
			deleteAsteroidByIndex(i);
		}
	}

	if (timer < time_between_levels) {
		timer += dt;
	}
	else {
		levelling_up = true;
		resetTimer();
	}
}

void AsteroidField::drawAsteroids() {
	for (Asteroid& asteroid : asteroids) {
		asteroid.draw();
	}
}

bool AsteroidField::isEmpty() const {
	return asteroids.empty();
}

bool AsteroidField::levellingUp() const {
	return levelling_up;
}

void AsteroidField::increaseAsteroidCountBy(int counter) {
	asteroid_count += counter;
}

void AsteroidField::resetTimer() {
	timer = 0;
}

void AsteroidField::deleteAsteroidByIndex(unsigned int index) {
	std::swap(asteroids[index], asteroids.back());
	asteroids.pop_back();
}

std::vector<Asteroid>& AsteroidField::getAsteroids() {
	return asteroids;
}

void AsteroidField::reset() {
	asteroid_count = 0;
	resetTimer();
	asteroids.clear();
	levelling_up = false;
}