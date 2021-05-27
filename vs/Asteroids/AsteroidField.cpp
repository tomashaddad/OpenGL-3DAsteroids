#include "AsteroidField.h"
#include "Math/Utility.h"
#include "Constants/AsteroidConstants.h"
#include "Constants/ArenaConstants.h"
#include "Texture/Texture.h"

AsteroidField::AsteroidField() :
	arena_radius(sqrt(3 * ARENA_DIM * ARENA_DIM)),
	asteroid_count(10),
	timer(0),
	time_between_levels(20),
	levelling_up(false) {}

void AsteroidField::loadTextures() {
	textures.push_back(Texture::loadTexture("./Assets/Asteroids/asteroid1.jpg"));
	textures.push_back(Texture::loadTexture("./Assets/Asteroids/asteroid2.jpg"));
	textures.push_back(Texture::loadTexture("./Assets/Asteroids/asteroid3.jpg"));
	textures.push_back(Texture::loadTexture("./Assets/Asteroids/asteroid4.jpg"));
}

void AsteroidField::launchAsteroidAtShip(Vector3D ship_position) {
	for (int i = 0; i < asteroid_count; ++i) {
		float speed = utility::randFloat(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
		Vector3D asteroid_position = Vector3D::randomUnit() * arena_radius;
		Vector3D asteroid_velocity = speed * Vector3D::normalise(ship_position - asteroid_position);
		asteroids.emplace_back(asteroid_position, asteroid_velocity, textures[utility::randInt(0, textures.size() - 1)]);
	}
}

void AsteroidField::updateAsteroids(float dt) {
	for (Asteroid& asteroid : asteroids) {
		asteroid.checkIfInArena(ARENA_DIM - 0.5);
		asteroid.update(dt);
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