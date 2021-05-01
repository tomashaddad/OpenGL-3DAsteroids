#ifndef I3D_ASTEROID_H
#define I3D_ASTEROID_H

#include <vector>

class Asteroid {
public:
	Asteroid(float radius = 1.0f, int sector_count = 36, int stack_count = 18);

	void build_vertices();
	void draw();


private:
	void add_vertex(float x, float y, float z);
	void add_normal(float nx, float ny, float nz);
	void add_indices(unsigned int i1, unsigned int i2, unsigned int i3);
	void build_interleaved_vertices();

	float radius;
	int sector_count;
	int stack_count;

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> line_indices;

	std::vector<float> interleaved_vertices;

	// Vertices are floats, so 4 bytes
	// Interleaved vertices have 3 vertices, 3 normals, so 6 * 4 = 24 bytes per 3 + 3 vertices
	// If you had 2 more floats for texture you would want 32 as in original Sphere.cpp
	int interleaved_stride;


};

#endif // I3D_ASTEROID_H