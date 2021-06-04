#include "Satellite.h"
#include "Constants/ArenaConstants.h"
#include "Math/Utility.h"

#include "GlutHeaders.h"

#include <iostream>

Satellite::Satellite() :
	position(sqrt(3) * ARENA_DIM * Vector3D::randomUnit()), // random position on the arena's bounding sphere
	rotation_axis(Vector3D::cross(position, Vector3D::randomUnit())),
	angle(utility::randFloat(0, 360)),
	speed(10) { }

void Satellite::update(float dt) {
	angle += speed * dt;
	if (angle >= 360) {
		angle = 0;
	}
}

void Satellite::draw() const {
	// The few times when scale -> translate -> rotate is correct!
	glEnable(GL_LIGHTING);
	glPushMatrix();
		glRotatef(angle, rotation_axis.X, rotation_axis.Y, rotation_axis.Z);
		glTranslatef(position.X, position.Y, position.Z);
		glLightfv(GL_LIGHT1, GL_POSITION, Vector3D::toArray(position).data());
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_LIGHTING);
		glutSolidSphere(10, 10, 10);
		glEnable(GL_LIGHTING);
	glPopMatrix();
	glDisable(GL_LIGHTING);
}