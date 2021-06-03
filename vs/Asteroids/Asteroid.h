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

	void decrementHealthBy(int num);
	void markForDeletion();
	bool isMarkedForDeletion() const;

	void reverseX();
	void reverseY();
	void reverseZ();

	const unsigned int id() const;
	const Vector3D& getPosition() const;
	const Vector3D& getVelocity() const;
	const int getHealth() const;
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
	Vector3D rotation_axis;
	float angle;
	float rotation_speed;
	int rotation_direction;
	int health;
	bool to_delete;

	int sectors;
	int stacks;

	std::vector<float> vertices;
	std::vector<float> uvs;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
};

#endif // I3D_ASTEROID_H