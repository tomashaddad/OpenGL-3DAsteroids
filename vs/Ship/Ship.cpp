#include "Ship.h"
#include "GlutHeaders.h"

#include "Model/Model.h"
#include "Math/Utility.h"

#include "Texture/Texture.h"

#include <iostream>
#include <vector>

#include <iostream>
#include <string>

Ship::Ship() :
	warning_radius(WARNING_RADIUS),
	collision_radius(COLLISION_RADIUS),
	logo(0) {	
	Model::loadOBJ("./Assets/Ship/airwing_triangulated_centered_scaled.obj",
		vertices, uvs, normals, triangles, materials); // vectors passed by reference
}

void Ship::loadTextures() {
	logo = Texture::loadTexture("./Assets/Ship/Star_Fox_logo_2015.jpeg");
}

void Ship::draw() const {
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glMultMatrixf(Quaternion::toMatrix(rotation).data());
		glRotatef(180, 0, 1, 0); // ship model is backwards lol 
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

			// phongE8 corresponds to the material that includes the logo
			if (materials[triangle->material_id].name == "phongE8") {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, logo);
			}

			glBegin(GL_TRIANGLES);
				if (materials[triangle->material_id].name == "phongE8") {
					glTexCoord2f(uvs[triangle->uvs[0]].X, uvs[triangle->uvs[0]].Y);
				}
				glNormal3f(normals[triangle->normals[0]].X, normals[triangle->normals[0]].Y, normals[triangle->normals[0]].Z);
				glVertex3f(vertices[triangle->vertices[0]].X, vertices[triangle->vertices[0]].Y, vertices[triangle->vertices[0]].Z);

				if (materials[triangle->material_id].name == "phongE8") {
					glTexCoord2f(uvs[triangle->uvs[1]].X, uvs[triangle->uvs[1]].Y);
				}
				glNormal3f(normals[triangle->normals[1]].X, normals[triangle->normals[1]].Y, normals[triangle->normals[1]].Z);
				glVertex3f(vertices[triangle->vertices[1]].X, vertices[triangle->vertices[1]].Y, vertices[triangle->vertices[1]].Z);

				if (materials[triangle->material_id].name == "phongE8") {
					glTexCoord2f(uvs[triangle->uvs[2]].X, uvs[triangle->uvs[2]].Y);
				}
				glNormal3f(normals[triangle->normals[2]].X, normals[triangle->normals[2]].Y, normals[triangle->normals[2]].Z);
				glVertex3f(vertices[triangle->vertices[2]].X, vertices[triangle->vertices[2]].Y, vertices[triangle->vertices[2]].Z);
			glEnd();

			if (materials[triangle->material_id].name == "phongE8") {
				glDisable(GL_TEXTURE_2D);
			}
		}
	glPopMatrix();
}

void Ship::move(Direction direction, float dt) {
	Vector3D ship_forward = rotation * Vector3D::forward();

	if (direction == Direction::forward) {
		position += ship_forward * SHIP_SPEED * dt;
	}
	else if (direction == Direction::backward) {
		position -= ship_forward * SHIP_SPEED * dt;
	}
}

// This is called if the rotation came from a mouse movement
// (World Quaternion) * (Ship Quaternion) defines rotations in LOCAL ship frame
void Ship::rotate(const Axis axis, const float dt, const float map, const float speed) {
	if (axis == Axis::x) {
		rotation *= Quaternion(Vector3D::right(), map * speed * dt);
	}
	else if (axis == Axis::y) {
		rotation *= Quaternion(Vector3D::up(), map * speed * dt);
	}
	else if (axis == Axis::z) {
		rotation *= Quaternion(Vector3D::forward(), map * speed * dt);
	}
}

// This is called if the rotation came from a barrel roll (i.e. A/D was pressed)
void Ship::roll(const Axis axis, const float dt) {
	// we forward the call to rotate but with 
	rotate(axis, dt, 1, BARREL_ROLL_SPEED);
}

const Vector3D& Ship::getPosition() const { return position; }
const Quaternion& Ship::getRotation() const { return rotation; }
const float& Ship::getWarningRadius() const { return warning_radius; }
const float& Ship::getCollisionRadius() const { return collision_radius; }

void Ship::reset() {
	position = Vector3D();
	rotation = Quaternion();
}
