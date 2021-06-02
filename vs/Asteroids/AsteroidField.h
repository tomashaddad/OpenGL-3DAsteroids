#ifndef I3D_ASTEROIDFIELD_H
#define I3D_ASTEROIDFIELD_H

#include "Asteroids/Asteroid.h"
#include "Math/Vector3D.h"

#include <vector>

class AsteroidField {
public:
	AsteroidField();

	void launchAsteroidAtShip(Vector3D ship_position);
	void updateAsteroids(float dt);
	void drawAsteroids();
	bool isEmpty() const;

	std::vector<Asteroid>& getAsteroids();

private:
	std::vector<unsigned int> textures;
	float arena_radius;
	float asteroid_count;
	float timer;
	float time_between_levels;
	bool levelling_up;

	std::vector<Asteroid> asteroids;
};

#endif // I3D_ASTEROIDFIELD_H