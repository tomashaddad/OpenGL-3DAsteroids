#include "Material.h"

std::ostream& operator<<(std::ostream& ostream, const Material& m) {
	ostream
		<< "Name: " << m.name << std::endl
		<< "Ns: " << m.Ns << std::endl
		<< "Ambient: " << m.ambient[0] << " " << m.ambient[1] << " " << m.ambient[2] << std::endl
		<< "Diffuse: " << m.diffuse[0] << " " << m.diffuse[1] << " " << m.diffuse[2] << std::endl
		<< "Specular: " << m.specular[0] << " " << m.specular[1] << " " << m.specular[2] << std::endl
		<< "Emission: " << m.emission[0] << " " << m.emission[1] << " " << m.emission[2] << std::endl
		<< "Ni: " << m.Ni << std::endl
		<< "Transparency: " << m.transparency << std::endl;

	return ostream;
}