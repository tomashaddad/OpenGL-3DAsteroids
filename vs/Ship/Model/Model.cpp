#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "Includes/tiny_obj_loader.h"

Model::Model(std::string filename) {
	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = "./Assets/Ship"; // Path to material files
	reader_config.triangulate = false;

	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(filename, reader_config)) {
		if (!reader.Error().empty()) {
			std::cerr << "TinyObjReader: " << reader.Error();
		}
		exit(1);
	}

	if (!reader.Warning().empty()) {
		std::cout << "TinyObjReader: " << reader.Warning();
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

				// Check if `normal_index` is zero or positive. negative = no normal data
				if (idx.normal_index >= 0) {
					tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
					tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
					tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
				}

				// Check if `texcoord_index` is zero or positive. negative = no texcoord data
				if (idx.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
				}
			}
			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}

	flatten3(attrib.vertices, vertices);
	flatten3(attrib.normals, normals);

	for (auto shape = shapes.begin(); shape < shapes.end(); ++shape) {
		processTriangles(*shape, triangles);
	}
}

// Flatten into groups of 3
void Model::flatten3(std::vector<float> collection, std::vector<Vector3D> &vector) {
	for (size_t vec_start = 0; vec_start < collection.size(); vec_start += 3) {
		vector.emplace_back(
			collection[vec_start],
			collection[vec_start + 1],
			collection[vec_start + 2]);
	}
}

void Model::processTriangles(const tinyobj::shape_t& shape, std::vector<Triangle>& triangles) {
		const std::vector<tinyobj::index_t>& indices = shape.mesh.indices;
		const std::vector<int>& material_ids = shape.mesh.material_ids;

		for (size_t index = 0; index < material_ids.size(); ++index) {
			// offset by 3 because values are grouped as vertex/normal/texture
			triangles.push_back(Triangle(
				{ indices[3 * index].vertex_index, indices[3 * index + 1].vertex_index, indices[3 * index + 2].vertex_index },
				{ indices[3 * index].normal_index, indices[3 * index + 1].normal_index, indices[3 * index + 2].normal_index })
			);
		}
}

const std::vector<Triangle>& Model::getTriangles() const { return triangles; }
const std::vector<Vector3D>& Model::getVertices() const { return vertices; }
const std::vector<Vector3D>& Model::getTextureCoords() const { return textures; }
const std::vector<Vector3D>& Model::getNormals() const { return normals;}