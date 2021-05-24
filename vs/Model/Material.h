#ifndef I3D_MATERIAL_H
#define I3D_MATERIAL_H

#include <string>
#include <array>

#include <algorithm> // std::copy

#include "GlutHeaders.h"

#include <iostream>

class Material {
public:
	Material(const std::string& name, float Ns, const float* ambient, const float* diffuse,
		const float* specular, const float* emission, float Ni, float transparency) :
		name(name), Ns(Ns), Ni(Ni), transparency(transparency) {
		// we know each is of size 3 (I know, magic number ...)
		for (int i = 0; i < 3; ++i) {
			this->ambient[i] = ambient[i];
			this->diffuse[i] = diffuse[i];
			this->specular[i] = specular[i];
			this->emission[i] = emission[i];
		}
	}

	std::string name;

	float Ns; // specular exponent, aka shininess
	std::array<float, 3> ambient; // Ka
	std::array<float, 3> diffuse; // Kd
	std::array<float, 3> specular; // Ks
	std::array<float, 3> emission; // Ke
	float Ni; // index of refraction
	float transparency; // d

	friend std::ostream& operator<<(std::ostream& ostream, const Material& m);
};

#endif