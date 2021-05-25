#include "AsteroidField.h"
#include "Math/Utility.h"
#include "Constants/AsteroidConstants.h"
#include "Constants/ArenaConstants.h"

AsteroidField::AsteroidField() :
	arena_radius(ARENA_DIM + 2 * ASTEROID_MAX_RADIUS), // spawn them a little far from arena
	asteroid_count(2),
	timer(0),
	time_between_levels(20),
	levelling_up(false) {}

void AsteroidField::launchAsteroidAtShip(Vector3D ship_position) {
	for (int i = 0; i < asteroid_count; ++i) {
		float speed = utility::getRandomFloatBetween(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
		Vector3D asteroid_position = utility::getRandomPointOnSphere(arena_radius);
		Vector3D asteroid_velocity = speed * Vector3D::normalise(ship_position - asteroid_position);
		asteroids.emplace_back(asteroid_position, asteroid_velocity);
	}
}

void AsteroidField::updateAsteroids(float dt) {
	for (Asteroid& asteroid : asteroids) {
		asteroid.update(dt, ARENA_DIM - 0.5);
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

std::vector<Asteroid>& AsteroidField::getAsteroids() {
	return asteroids;
}