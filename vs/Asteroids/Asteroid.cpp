#include <cmath>

#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Math/Utility.h"

#include "Constants/AsteroidConstants.h"

#include <iostream>

Asteroid::Asteroid(Vector3D position, Vector3D velocity) :
	position(position),
	velocity(velocity),
	interleaved_stride(24),
	radius(utility::getRandomFloatBetween(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE)),
	sector_count(ASTEROID_SECTOR_COUNT),
	stack_count(ASTEROID_STACK_COUNT) {	
	std::cout << "Asteroid spawned at: " << position << " with velocity " << velocity << std::endl;
	buildVertices();
}

void Asteroid::draw() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(position.X, position.Y, position.Z);
		glColor3f(1.0, 1.0, 1.0);
		glutWireSphere(200, 20, 20);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Asteroid::update(float dt) {
	position += velocity * dt;
}

void Asteroid::buildVertices() {
	const float pi = acos(-1);

	float x, y, z, xy;
	float nx, ny, nz;

	float sector_step = 2 * pi / sector_count; // number of vertical slices
	float stack_step = pi / stack_count; // number of horizontal slices
	float sector_angle, stack_angle;

	for (int i = 0; i <= stack_count; ++i) {
		stack_angle = pi / 2 - i * stack_step;
		// radius = 1 to start with unit radius
		xy = cosf(stack_angle);
		z = sinf(stack_angle);

		for (int j = 0; j <= sector_count; ++j) {
			sector_angle = j * sector_step;

			x = xy * cosf(sector_angle);
			y = xy * sinf(sector_angle);
			addVertex(x, y, z);

			float length_inv = 1.0f / radius;
			nx = x * length_inv;
			ny = y * length_inv;
			nz = z * length_inv;

			addNormal(nx, ny, nz);
		}
	}

	unsigned int k1, k2;
	for (int i = 0; i < stack_count; ++i) {
		k1 = i * (sector_count + 1);
		k2 = k1 + sector_count + 1;

		for (int j = 0; j < sector_count; ++j, ++k1, ++k2) {
			if (i != 0) {
				addIndices(k1, k2, k1 + 1);
			}

			if (i != (stack_count - 1)) {
				addIndices(k1 + 1, k2, k2 + 1);
			}
		}
	}
}

void Asteroid::addVertex(float x, float y, float z) {
	vertices.emplace_back(x, y, z);
}

void Asteroid::addNormal(float nx, float ny, float nz) {
	normals.emplace_back(nx, ny, nz);
}

void Asteroid::addIndices(unsigned int i1, unsigned int i2, unsigned int i3) {
	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);
}