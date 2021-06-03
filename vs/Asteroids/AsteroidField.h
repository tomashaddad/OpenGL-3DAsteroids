#ifndef I3D_ASTEROIDFIELD_H
#define I3D_ASTEROIDFIELD_H

#include "Asteroids/Asteroid.h"
#include "Math/Vector3D.h"

#include <vector>

class AsteroidField {
public:
	AsteroidField();

	void launchAsteroidsAtShip(Vector3D ship_position);
	void updateAsteroids(float dt);
	void drawAsteroids();
	bool isEmpty() const;
	bool levellingUp() const;
	void increaseAsteroidCountBy(int counter);
	void resetTimer();
	void deleteAsteroidByIndex(unsigned int index);
	std::vector<Asteroid>& getAsteroids();
	
	void reset();

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