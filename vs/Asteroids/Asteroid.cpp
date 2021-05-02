#define _USE_MATH_DEFINES
#include <cmath>

#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Math/Utility.h"

#include <iostream>

Asteroid::Asteroid(float radius, int sector_count, int stack_count) : interleaved_stride(24) {
	this->radius = radius;
	this->sector_count = sector_count;
	this->stack_count = stack_count;
	
	buildVertices();
}

void Asteroid::buildVertices() {
	const float pi = M_PI;

	float x, y, z, xy;
	float nx, ny, nz;

	float sector_step = 2 * pi / sector_count; // number of vertical slices
	float stack_step = pi / stack_count; // number of horizontal slices
	float sector_angle, stack_angle;

	for (int i = 0; i <= stack_count; ++i) {
		stack_angle = pi / 2 - i * stack_step;
		xy = radius * cosf(stack_angle);
		z = radius * sinf(stack_angle);

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
	buildInterleavedIndices();
}

void Asteroid::buildInterleavedIndices() {
	// Swap?
	// std::vector<float>().swap(interleaved_vertices);

	std::size_t i;
	std::size_t count = vertices.size();

	for (i = 0; i < count; i += 3) {
		interleaved_vertices.push_back(vertices[i]);
		interleaved_vertices.push_back(vertices[i + 1]);
		interleaved_vertices.push_back(vertices[i + 2]);

		interleaved_vertices.push_back(normals[i]);
		interleaved_vertices.push_back(normals[i + 1]);
		interleaved_vertices.push_back(normals[i + 2]);
	}
}

void Asteroid::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, interleaved_stride, &interleaved_vertices[0]);
	glNormalPointer(GL_FLOAT, interleaved_stride, &interleaved_vertices[3]);

	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

void Asteroid::addVertex(float x, float y, float z) {
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

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