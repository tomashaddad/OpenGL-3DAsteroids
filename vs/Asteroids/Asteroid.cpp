#define _USE_MATH_DEFINES
#include <cmath>

#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Math/Utility.h"

#include "Constants/AsteroidConstants.h"

#include <iostream>

Asteroid::Asteroid(Vector3D position, Vector3D velocity) :
	asteroid_id(nextID()),
	position(position),
	velocity(velocity),
	interleaved_stride(24),
	inArena(false),
	radius(utility::getRandomFloatBetween(ASTEROID_MIN_RADIUS, ASTEROID_MAX_RADIUS)),
	mass((4.0f/3.0f) * M_PI * pow(radius, 3)), // set mass as volume of sphere
	sector_count(ASTEROID_SECTOR_COUNT),
	stack_count(ASTEROID_STACK_COUNT) {	
	buildVertices();
}

unsigned int Asteroid::nextID() {
	static unsigned int i = 0;
	return ++i;
}

const unsigned int Asteroid::id() const { return asteroid_id; }

void Asteroid::draw() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glScalef(radius, radius, radius);
		glColor3f(1.0, 1.0, 1.0);
		glutWireSphere(1, 20, 20);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Asteroid::update(const float dt) {
	position += velocity * dt;
}

void Asteroid::checkIfInArena(const float arena_dimension) {
	if (!inArena) {
		inArena =
			position.X + radius < arena_dimension&&
			position.X - radius > -arena_dimension &&
			position.Y + radius < arena_dimension&&
			position.Y - radius > -arena_dimension &&
			position.Z + radius < arena_dimension&&
			position.Z - radius > -arena_dimension;
	}
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

// slightly nudge when reversing so they don't get stuck or jitter
void Asteroid::reverseX() {
	position.X = position.X < 0 ? position.X + 1 : position.X - 1;
	velocity.X = -velocity.X;
}
void Asteroid::reverseY() {
	position.Y = position.Y < 0 ? position.Y + 1 : position.Y - 1;
	velocity.Y = -velocity.Y;
}

void Asteroid::reverseZ() {
	position.Z = position.Z < 0 ? position.Z + 1 : position.Z - 1;
	velocity.Z = -velocity.Z;
}

const Vector3D& Asteroid::getPosition() const { return position; }
const Vector3D& Asteroid::getVelocity() const { return velocity; }
void Asteroid::setVelocity(const Vector3D& velocity) { this->velocity = velocity; }
const float Asteroid::getRadius() const { return radius; }
const float Asteroid::getMass() const { return mass; }
const bool Asteroid::isInArena() const { return inArena; }