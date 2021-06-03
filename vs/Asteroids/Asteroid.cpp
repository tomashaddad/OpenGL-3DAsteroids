#define _USE_MATH_DEFINES
#include <cmath>

#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Math/Utility.h"

#include "Constants/AsteroidConstants.h"

#include <iostream>

Asteroid::Asteroid(Vector3D position, Vector3D velocity, unsigned int texture)
	: asteroid_id(nextID())
	, position(position)
	, velocity(velocity)
	, inArena(false)
	, texture(texture)
	, radius(utility::randFloat(ASTEROID_MIN_RADIUS, ASTEROID_MAX_RADIUS))
	, mass((4.0f / 3.0f)* M_PI* pow(radius, 3))
	//, rotation(Quaternion::random())
	, rotation_axis(Vector3D::randomUnit())
	, angle(0)
	, rotation_speed(utility::randFloat(ASTEROID_MIN_ROTATION_SPEED, ASTEROID_MAX_ROTATION_SPEED))
	, rotation_direction(utility::randSign())
	, health(utility::mapToRange(radius, ASTEROID_MIN_RADIUS, ASTEROID_MAX_RADIUS, ASTEROID_MIN_HEALTH, ASTEROID_MAX_HEALTH))
	, to_delete(false)
	, sectors(ASTEROID_SECTOR_COUNT)
	, stacks(ASTEROID_STACK_COUNT) {	
	buildVertices();
}

unsigned int Asteroid::nextID() {
	static unsigned int i = 0;
	return ++i;
}

const unsigned int Asteroid::id() const { return asteroid_id; }

void Asteroid::draw() {
	glEnable(GL_LIGHTING);
	glPointSize(10);
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		//glMultMatrixf(Quaternion::toMatrix(rotation).data());
		glRotatef(angle, rotation_axis.X, rotation_axis.Y, rotation_axis.Z);
		glScalef(radius, radius, radius);
		glColor3f(1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);

		float ambient[] = { 1.0, 1.0, 1.0, 1.0 };
		float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		float specular[] = { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 128);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 2 * sizeof(float), &uvs[0]); // 2 tex coords per 8 bytes
		glNormalPointer(GL_FLOAT, 0, &vertices[0]); // unit sphere, so norms = verts
		glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glDisable(GL_LIGHTING);
}

void Asteroid::update(const float dt) {
	position += velocity * dt;

	angle += rotation_speed * dt;

	if (health <= 0) {
		markForDeletion();
	}
}

void Asteroid::checkIfInArena(const float arena_dimension) {
	if (!inArena) {
		inArena
			 = position.X + radius < arena_dimension
			&& position.X - radius > -arena_dimension
			&& position.Y + radius < arena_dimension
			&& position.Y - radius > -arena_dimension
			&& position.Z + radius < arena_dimension
			&& position.Z - radius > -arena_dimension;
	}
}

void Asteroid::buildVertices() {
	const float pi = acos(-1);

	float x, y, z, xz;
	float nx, ny, nz;

	float sector_step = 2 * pi / sectors; // THETA STEP
	float stack_step = pi / stacks; // PHI STEP

	float theta, phi;

	// adds sector# of vertices at poles
	for (int i = 0; i <= stacks; ++i) {
		phi = pi / 2 - i * stack_step;
		y = sin(phi);
		xz = cos(phi);
		for (int j = 0; j <= sectors; ++j) {
			theta = j * sector_step;
			x = sin(theta) * cos(phi);
			z = cos(theta) * cos(phi);

			float fudge = utility::randFloat(0.90, 1.1);

			if (j > 0 && j < stacks && i > 0 && i < sectors) {
				x *= fudge;
				z *= fudge;
			}

			addVertex(x, y, z);
			addUV((float)j / sectors, (float)i / sectors);
		}
	}

	unsigned int k1, k2;
	for (int i = 0; i < stacks; ++i) {
		k1 = i * (sectors + 1);
		k2 = k1 + sectors + 1;

		for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
			// two triangles per face excluding first and last stacks
			if (i != 0) {
				addIndices(k1, k2, k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stacks - 1)) {
				addIndices(k1 + 1, k2, k2 + 1);
			}

		}
	}
}

void Asteroid::addVertex(float x, float y, float z) {
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void Asteroid::addUV(float u, float v) {
	uvs.push_back(u);
	uvs.push_back(v);
}

// Technically not needed but I'm leaving it anyway
void Asteroid::addNormal(float nx, float ny, float nz) {
	normals.push_back(nx);
	normals.push_back(ny);
	normals.push_back(nz);
}

void Asteroid::addIndices(unsigned int i1, unsigned int i2, unsigned int i3) {
	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);
}

void Asteroid::decrementHealthBy(int num) {
	health -= num;
}

void Asteroid::markForDeletion() {
	to_delete = true;
}

bool Asteroid::isMarkedForDeletion() const {
	return to_delete;
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
const int Asteroid::getHealth() const { return health; }
void Asteroid::setVelocity(const Vector3D& velocity) { this->velocity = velocity; }
const float Asteroid::getRadius() const { return radius; }
const float Asteroid::getMass() const { return mass; }
const bool Asteroid::isInArena() const { return inArena; }