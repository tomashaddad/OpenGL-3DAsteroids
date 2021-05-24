#include "Triangle.h"

std::ostream& operator<<(std::ostream& ostream, const Triangle& v) {
	ostream << "Vertices: " << v.vertices[0] << " " << v.vertices[1] << " " << v.vertices[2] << std::endl;
	ostream << "Normals: " << v.normals[0] << " " << v.normals[1] << " " << v.normals[2] << std::endl;

	return ostream;
}