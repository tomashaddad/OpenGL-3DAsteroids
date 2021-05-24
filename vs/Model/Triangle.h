#ifndef I3D_TRIANGLE_H
#define I3D_TRIANGLE_H

#include <iostream>
#include <array>

class Triangle {
public:
	Triangle(std::array<int, 3> vertices, std::array<int, 3> uvs, std::array<int, 3> normals, unsigned int material_id) :
		vertices(vertices), uvs(uvs), normals(normals), material_id(material_id) {}

	std::array<int, 3> vertices;
	std::array<int, 3> uvs;
	std::array<int, 3> normals;
	unsigned int material_id;

	friend std::ostream& operator<<(std::ostream& ostream, const Triangle& v);
};

#endif // I3D_TRIANGLE_H