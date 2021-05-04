#include "Ship.h"
#include "GlutHeaders.h"

Ship::Ship() :
	position(Vector3D{ 0, 0, 0 }) {}

Ship::Ship(float x, float y, float z) :
	position(Vector3D{ x, y, z }) {}

Ship::Ship(Vector3D position) :
	position(position) {}

void Ship::draw() const {
	glPushMatrix();
		glMultMatrixf(Quaternion::toMatrix(rotation).data());
		glutWireCube(2);
	glPopMatrix();
}

void Ship::move(const Move movement, const float dt) {
	if (movement == Move::up) {
		rotation *= Quaternion(Vector3D::right(), -100 * dt);
	}
	else if (movement == Move::down) {
		rotation *= Quaternion(Vector3D::right(), 100 * dt);
	}
	else if (movement == Move::left) {
		rotation *= Quaternion(Vector3D::up(), 100 * dt);
	}
	else if (movement == Move::right) {
		rotation *= Quaternion(Vector3D::up(), -100 * dt);
	}
	else if (movement == Move::forward) {
		rotation *= Quaternion(Vector3D::backward(), -100 * dt);
	}
	else if (movement == Move::backward) {
		rotation *= Quaternion(Vector3D::backward(), 100 * dt);
	}
}

const Vector3D& Ship::getPosition() const {
	return position;
}