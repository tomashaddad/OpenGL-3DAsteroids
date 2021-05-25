#ifndef I3D_ASTEROID_H
#define I3D_ASTEROID_H

#include "Math/Vector3D.h"
#include <vector>

class Asteroid {
public:
	Asteroid(Vector3D position, Vector3D velocity);
	void buildVertices();
	void draw();
	void update(const float dt, const float arena_dimension);
	bool checkIfInArena(const float arena_dimension) const;
	void displace(const Vector3D& displacement);

	void reverseX();
	void reverseY();
	void reverseZ();

	const unsigned int id() const;
	const Vector3D& getPosition() const;
	const Vector3D& getVelocity() const;
	void setVelocity(const Vector3D& velocity);
	const float getRadius() const;
	const float getMass() const;
	const bool isInArena() const;

private:
	static unsigned int nextID();
	void addVertex(float x, float y, float z);
	void addNormal(float nx, float ny, float nz);
	void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);

	unsigned int id_num;
	Vector3D position;
	Vector3D velocity;

	bool inArena;

	float radius;
	float mass;
	int sector_count;
	int stack_count;

	std::vector<Vector3D> vertices;
	std::vector<Vector3D> normals;
	std::vector<unsigned int> indices;

	std::vector<float> interleaved_vertices;

	// Vertices are floats, so 4 bytes
	// Interleaved vertices have 3 vertices, 3 normals, so 6 * 4 = 24 bytes per 3 + 3 vertices
	// If you had 2 more floats for texture you would want 32 as in original Sphere.cpp
	int interleaved_stride;
};

#endif // I3D_ASTEROID_H