#include "Ship.h"
#include "Constants/ShipConstants.h"
#include "GlutHeaders.h"

Ship::Ship() :
	position(Vector3D{ 0, 0, 0 }) {}

Ship::Ship(float x, float y, float z) :
	position(Vector3D{ x, y, z }) {}

Ship::Ship(Vector3D position) :
	position(position) {}

void Ship::draw() const {
	glDisable(GL_LIGHTING);

	glPushMatrix();
		glMultMatrixf(Quaternion::toMatrix(rotation).data());

		//glBegin(GL_LINES);
		//	// positive x: red, y: green, z: blue
		//	glColor3f(0.0, 0.0, 0.0);
		//	glVertex3f(-5.0, 0.0, 0.0);
		//	glColor3f(1.0, 0.0, 0.0);
		//	glVertex3f(5.0, 0.0, 0.0);

		//	glColor3f(0.0, 0.0, 0.0);
		//	glVertex3f(0.0, -5.0, 0.0);
		//	glColor3f(0.0, 1.0, 0.0);
		//	glVertex3f(0.0, 5.0, 0.0);

		//	glColor3f(0.0, 0.0, 0.0);
		//	glVertex3f(0.0, 0.0, -5.0);
		//	glColor3f(0.0, 0.0, 1.0);
		//	glVertex3f(0.0, 0.0, 5.0);
		//glEnd();

		glColor3f(1.0, 1.0, 1.0);
		glutWireCube(8);
	glPopMatrix();
	
	glEnable(GL_LIGHTING);

}

// (World Quaternion) * (Ship Quaternion) defines rotations in local ship frame
void Ship::rotate(const Axis axis, const Direction direction, const float dt) {
	int sign = direction == Direction::positive ? 1 : -1;
	float speed = sign * ROTATION_SPEED;

	if (axis == Axis::x) {
		rotation = Quaternion(Vector3D::right(), speed * dt) * rotation;
	}
	else if (axis == Axis::y) {
		rotation = Quaternion(Vector3D::up(), speed * dt) * rotation;
	}
	else if (axis == Axis::z) {
		rotation = Quaternion(Vector3D::forward(), speed * dt) * rotation;
	}
}

void Ship::yaw(float angle, float dt) {
	rotation = Quaternion(Vector3D::up(), angle * 100 * dt) * rotation;
}

void Ship::pitch(float angle, float dt) {
	rotation = Quaternion(Vector3D::right(), angle * 100 * dt) * rotation;
}

void Ship::roll(float angle, float dt) {
	rotation = Quaternion(Vector3D::forward(), angle * dt) * rotation;
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