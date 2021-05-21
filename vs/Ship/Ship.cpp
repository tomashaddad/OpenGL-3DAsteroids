#include "Ship.h"
#include "Constants/ShipConstants.h"
#include "GlutHeaders.h"

#include "Math/Utility.h"

#include <iostream>

#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "Includes/tiny_obj_loader.h"

Ship::Ship() :
	warning_radius(WARNING_RADIUS),
	collision_radius(COLLISION_RADIUS) {
	std::string filename = "C:\\dev\\I3DGraphics\\GraphicsA2\\vs\\Assets\\airwing_triangulated.obj";

	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = "C:\\dev\\I3DGraphics\\GraphicsA2\\vs\\Assets\\"; // Path to material files
	reader_config.triangulate = true;

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

	// EVERY 3 ENTRIES IN FACES CORRESPONDS TO ONE FACE
	// I.E. THE 3 VERTICES THEY POINT TO CREATE A TRIANGLE
	// populate faces indices
	for (size_t shape = 0; shape < shapes.size(); ++shape) {
		const std::vector<tinyobj::index_t> indices = shapes[shape].mesh.indices;

		for (size_t face = 0; face < indices.size() - 2; face += 3) {
			faces.push_back(indices[face].vertex_index);
			faces.push_back(indices[face + 1].vertex_index);
			faces.push_back(indices[face + 2].vertex_index);
		}
	}


	// transform flattened vertiecs array into groups of vertices
	for (size_t vec_start = 0; vec_start < attrib.vertices.size(); vec_start += 3) {
		vertices.emplace_back(
			attrib.vertices[vec_start],
			attrib.vertices[vec_start + 1],
			attrib.vertices[vec_start + 2]);
	}

	//this->normals = attrib.normals;

	std::cout << vertices[faces[0]] << std::endl;
}

Ship::Ship(float x, float y, float z) : Ship() {
	position = Vector3D{ x, y, z };
}

Ship::Ship(Vector3D position) : Ship() {
	position = position;
}

void Ship::draw() const {
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glMultMatrixf(Quaternion::toMatrix(rotation).data());
		glScalef(50, 50, 50);
		
		utility::drawAxes(5.0f);

		glLineWidth(1);
		glColor3f(1.0, 1.0, 1.0);

		glBegin(GL_TRIANGLES);
		for (size_t face = 0; face < faces.size() - 3; face += 3) {
			glVertex3f(vertices[faces[face]].X, vertices[faces[face]].Y, vertices[faces[face]].Z);
			glVertex3f(vertices[faces[face + 1]].X, vertices[faces[face + 1]].Y, vertices[faces[face + 1]].Z);
			glVertex3f(vertices[faces[face + 2]].X, vertices[faces[face + 2]].Y, vertices[faces[face + 2]].Z);
		}
		glEnd();


	glPopMatrix();
	
	glEnable(GL_LIGHTING);

}

void Ship::move(Direction direction, float dt) {
	Vector3D ship_forward = rotation * Vector3D::forward();

	if (direction == Direction::forward) {
		position += ship_forward * dt;
	}
	else if (direction == Direction::backward) {
		position -= ship_forward * dt;
	}
}

// (World Quaternion) * (Ship Quaternion) defines rotations in local ship frame
void Ship::rotate(const Axis axis, const float angle) {
	if (axis == Axis::x) {
		rotation *= Quaternion(Vector3D::right(), angle);
	}
	else if (axis == Axis::y) {
		rotation *= Quaternion(Vector3D::up(), angle);
	}
	else if (axis == Axis::z) {
		rotation *= Quaternion(Vector3D::forward(), angle);
	}
}

const Vector3D& Ship::getPosition() const { return position; }
const Quaternion& Ship::getRotation() const { return rotation; }
const float& Ship::getWarningRadius() const { return warning_radius; }
const float& Ship::getCollisionRadius() const { return collision_radius; }

void Ship::reset() {
	position = Vector3D();
	rotation = Quaternion();
}
