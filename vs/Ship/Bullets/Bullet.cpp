#include "Bullet.h"
#include "Constants/BulletConstants.h"
#include "GlutHeaders.h"

Bullet::Bullet(Vector3D position, Vector3D velocity) :
	position(position),
	velocity(velocity),
	to_delete(false) {}

void Bullet::update(float dt) {
	position += velocity * BULLET_SPEED * dt;
}

void Bullet::draw() const {
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glScalef(0.5, 0.5, 0.5);
		glutSolidSphere(1, 5, 5);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

const Vector3D& Bullet::getPosition() const {
	return position;
}

void Bullet::markForDeletion() {
	to_delete = true;
}
bool Bullet::markedForDeletion() {
	return to_delete;
}