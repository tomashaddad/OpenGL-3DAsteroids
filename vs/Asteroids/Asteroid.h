#ifndef I3D_ASTEROID_H
#define I3D_ASTEROID_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"
#include <vector>

class Asteroid {
public:
	Asteroid(Vector3D position, Vector3D velocity, unsigned int texture);
	void buildVertices();
	void draw();
	void update(const float dt);
	void checkIfInArena(const float arena_dimension);

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
	void addUV(float u, float v);
	void addNormal(float nx, float ny, float nz);
	void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);

	unsigned int asteroid_id;
	Vector3D position;
	Vector3D velocity;

	bool inArena;

	unsigned int texture;
	float radius;
	float mass;
	Quaternion rotation;
	float rotation_speed;
	int rotation_direction;

	int sectors;
	int stacks;

	std::vector<Vector3D> vertices;
	std::vector<Vector3D> uvs;
	std::vector<Vector3D> normals;
	std::vector<unsigned int> indices;
};

#endif // I3D_ASTEROID_H