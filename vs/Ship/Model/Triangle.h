#ifndef I3D_TRIANGLE_H
#define I3D_TRIANGLE_H

#include <iostream>
#include <array>

class Triangle {
public:
	Triangle(std::array<int, 3> vertices, std::array<int, 3> normals) : vertices(vertices), normals(normals) {}
	std::array<int, 3> vertices;
	std::array<int, 3> normals;

	friend std::ostream& operator<<(std::ostream& ostream, Triangle& v);
	friend std::ostream& operator<<(std::ostream& ostream, const Triangle& v);
};

#endif // I3D_TRIANGLE_H