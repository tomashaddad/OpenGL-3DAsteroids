#include "Ship.h"
#include "Constants/ShipConstants.h"
#include "GlutHeaders.h"

#include <iostream>

Ship::Ship() :
	position(Vector3D{ 0, 0, 0 }) {}

Ship::Ship(float x, float y, float z) :
	position(Vector3D{ x, y, z }) {}

Ship::Ship(Vector3D position) :
	position(position) {}

void Ship::draw() const {
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glMultMatrixf(Quaternion::toMatrix(rotation).data());

		glBegin(GL_LINES);
			// positive x: red, y: green, z: blue
			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(-5.0, 0.0, 0.0);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(5.0, 0.0, 0.0);

			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, -5.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 5.0, 0.0);

			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, -5.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, 5.0);
		glEnd();

		glLineWidth(3);
		glBegin(GL_LINES);
		// positive x: red, y: green, z: blue
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(1.0, 1.0, 0.0);
		Vector3D forward = Vector3D::forward();
		glVertex3f(forward.X * 20, forward.Y * 20, forward.Z * 20);
		glEnd();
		glLineWidth(1);

		glColor3f(1.0, 1.0, 1.0);
		glutWireCube(3);

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

	std::cout << rotation << std::endl;
	std::cout << Quaternion::magnitude(rotation) << std::endl;
}

const Vector3D& Ship::getPosition() const {
	return position;
}

const Quaternion& Ship::getRotation() const {
	return rotation;
}

void Ship::reset() {
	position = Vector3D();
	rotation = Quaternion();
}

bool Ship::collidesWith(Collidable& other, Type type) {
	return false;
}

void Ship::handleCollision(Collidable &other, Type type) {
	if (type == Type::meteor) {

	}

	if (type == Type::wall) {

	}
}

void Ship::reactToCollision(Collidable& other, Type type) {

}