#ifndef I3D_MODEL_H
#define I3D_MODEL_H

#include "Includes/tiny_obj_loader.h"

#include "Math/Vector3D.h"
#include "Triangle.h"
#include "Material.h"

#include <vector>

class Model {
public:
	static void loadOBJ(std::string filename, std::vector<Vector3D>& vertices, std::vector<Vector3D>& uvs,
		std::vector<Vector3D>& normals, std::vector<Triangle>& triangles, std::vector<Material>& materials);

private:
	static void flatten3(std::vector<float> collection, std::vector<Vector3D>& vector);
	static void flatten2(std::vector<float> collection, std::vector<Vector3D>& vector);
	static void processTriangles(const tinyobj::shape_t& shape, std::vector<Triangle>& triangles);
	static void processMaterials(const std::vector<tinyobj::material_t>& objmaterials, std::vector<Material>& materials);
};

#endif // I3D_MODEL_H