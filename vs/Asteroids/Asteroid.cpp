#define _USE_MATH_DEFINES
#include <cmath>

#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Math/Utility.h"

#include "Constants/AsteroidConstants.h"

#include "Texture/Texture.h"

#include <iostream>

Asteroid::Asteroid(Vector3D position, Vector3D velocity, unsigned int texture) :
	asteroid_id(nextID()),
	position(position),
	velocity(velocity),
	inArena(false),
	texture(texture),
	radius(utility::randFloat(ASTEROID_MIN_RADIUS, ASTEROID_MAX_RADIUS)), // used in glScalef(. . .)
	mass((4.0f/3.0f) * M_PI * pow(radius, 3)), // set mass as volume of sphere (4/3*pi*r^3)
	rotation(Quaternion::random()),
	rotation_speed(utility::randFloat(ASTEROID_MIN_ROTATION_SPEED, ASTEROID_MAX_ROTATION_SPEED)),
	rotation_direction(utility::randSign()),
	sectors(ASTEROID_SECTOR_COUNT),
	stacks(ASTEROID_STACK_COUNT) {	
	buildVertices();
}

unsigned int Asteroid::nextID() {
	static unsigned int i = 0;
	return ++i;
}

const unsigned int Asteroid::id() const { return asteroid_id; }

void Asteroid::draw() {
	glPointSize(10);
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glMultMatrixf(Quaternion::toMatrix(rotation).data());
		glScalef(radius, radius, radius);
		glColor3f(1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);

		float ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		float specular[] = { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 128);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i <= indices.size() - 3; i += 3) {
			glTexCoord2f(uvs[indices[i]].X, uvs[indices[i]].Y);
			glNormal3f(normals[indices[i]].X, normals[indices[i]].Y, normals[indices[i]].Z);
			glVertex3f(vertices[indices[i]].X, vertices[indices[i]].Y, vertices[indices[i]].Z);

			glTexCoord2f(uvs[indices[i + 1]].X, uvs[indices[i + 1]].Y);
			glNormal3f(normals[indices[i + 1]].X, normals[indices[i + 1]].Y, normals[indices[i + 1]].Z);
			glVertex3f(vertices[indices[i + 1]].X, vertices[indices[i + 1]].Y, vertices[indices[i + 1]].Z);

			glTexCoord2f(uvs[indices[i + 2]].X, uvs[indices[i + 2]].Y);
			glNormal3f(normals[indices[i + 2]].X, normals[indices[i + 2]].Y, normals[indices[i + 2]].Z);
			glVertex3f(vertices[indices[i + 2]].X, vertices[indices[i + 2]].Y, vertices[indices[i + 2]].Z);
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Asteroid::update(const float dt) {
	position += velocity * dt;

	// rotate asteroid according to its local up axis

	rotation *= Quaternion(Vector3D::up(), rotation_speed * rotation_direction * dt);
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

			addVertex(x, y, z);
			addNormal(x, y, z);
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
	vertices.emplace_back(x, y, z);
}

void Asteroid::addUV(float u, float v) {
	uvs.emplace_back(u, v, 0);
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