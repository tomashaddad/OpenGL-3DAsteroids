#ifndef I3D_MATERIAL_H
#define I3D_MATERIAL_H

#include <string>
#include <array>

class Material {
	std::string name;
	int id; // material id (for the ship it's 0-16)

	float Ns; // specular exponent
	std::array<float, 3> ambient; // Ka
	std::array<float, 3> diffuse; // Kd
	std::array<float, 3> specular; // Ks
	std::array<float, 3> emission; // Ke
	std::array<float, 3> optical; // optical density, Ni
	float transparency; // d
};

#endif