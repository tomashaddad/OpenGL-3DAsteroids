#ifndef I3D_MODEL_H
#define I3D_MODEL_H

#include "Includes/tiny_obj_loader.h"

#include "Math/Vector3D.h"
#include "Triangle.h"

#include <vector>

class Model {
public:
	Model() = default;
	Model(std::string filename);
	
	const std::vector<Triangle>& getTriangles() const;
	const std::vector<Vector3D>& getVertices() const;
	const std::vector<Vector3D>& getTextureCoords() const;
	const std::vector<Vector3D>& getNormals() const;

private:
	void flatten3(std::vector<float> collection, std::vector<Vector3D> &vector);
	void processTriangles(const tinyobj::shape_t& shape, std::vector<Triangle>& triangles);

	std::vector<Triangle> triangles;
	std::vector<Vector3D> vertices;
	std::vector<Vector3D> textures;
	std::vector<Vector3D> normals;
};

#endif // I3D_MODEL_H