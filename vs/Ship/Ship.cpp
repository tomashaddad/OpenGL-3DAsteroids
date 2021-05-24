#include "Ship.h"
#include "Constants/ShipConstants.h"
#include "GlutHeaders.h"

#include "Model/Model.h"
#include "Math/Utility.h"

#include <iostream>
#include <vector>

#include <iostream>
#include <string>

Ship::Ship() :
	warning_radius(WARNING_RADIUS),
	collision_radius(COLLISION_RADIUS) {
	std::string obj = "./Assets/Ship/airwing_triangulated_centered_scaled.obj";
	
	Model::loadOBJ(obj, vertices, uvs, normals, triangles, materials); // vectors passed by reference
}
bool flag = true;
void Ship::draw() const {
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glMultMatrixf(Quaternion::toMatrix(rotation).data());
		glRotatef(90, 1, 1, 1); // ship model is backwards lol 
		glScalef(10, 10, 10);
		
		glPushMatrix();
		glRotatef(-180, 0, 1, 0); // undo fixing ship TODO: JUST FIX THE MODEL
		utility::drawAxes(1.0f);
		glPopMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);

		for (auto triangle = triangles.begin(); triangle != triangles.end(); ++triangle) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, materials[triangle->material_id].ambient.data());
			glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[triangle->material_id].diffuse.data());
			glMaterialfv(GL_FRONT, GL_SPECULAR, materials[triangle->material_id].specular.data());
			glMaterialf(GL_FRONT, GL_SHININESS, 128);

			glBegin(GL_TRIANGLES);
				glNormal3f(normals[triangle->normals[0]].X, normals[triangle->normals[0]].Y, normals[triangle->normals[0]].Z);
				glVertex3f(vertices[triangle->vertices[0]].X, vertices[triangle->vertices[0]].Y, vertices[triangle->vertices[0]].Z);

				glNormal3f(normals[triangle->normals[1]].X, normals[triangle->normals[1]].Y, normals[triangle->normals[1]].Z);
				glVertex3f(vertices[triangle->vertices[1]].X, vertices[triangle->vertices[1]].Y, vertices[triangle->vertices[1]].Z);

				glNormal3f(normals[triangle->normals[2]].X, normals[triangle->normals[2]].Y, normals[triangle->normals[2]].Z);
				glVertex3f(vertices[triangle->vertices[2]].X, vertices[triangle->vertices[2]].Y, vertices[triangle->vertices[2]].Z);
			glEnd();
		}
	glPopMatrix();
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
