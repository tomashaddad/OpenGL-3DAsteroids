#include "Utility.h"
#include "GlutHeaders.h"

#include <random>

// a must be less than b
float utility::getRandomFloatBetween(float a, float b) {
	std::random_device engine;
	std::uniform_real_distribution<float> real_dist =
		std::uniform_real_distribution<float>{ a, b };
	return real_dist(engine);
}

float utility::toRadians(float angle) {
	return angle * pi / 180.0f;
}

float utility::toDegrees(float angle) {
	return angle * 180.0f / pi;
}

float utility::mapToRange(float value, float old_min, float old_max, float new_min, float new_max) {
	const float old_range = old_max - old_min;
	const float new_range = new_max - new_min;
	return (value - old_min) * new_range / old_range + new_min;
}

// TODO: This probably doesn't belong here
void utility::drawAxes(float size) {
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glScalef(size, size, size);
		glBegin(GL_LINES);
			// positive x: red, y: green, z: blue
			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(-1.0, 0.0, 0.0);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(1.0, 0.0, 0.0);

			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, -1.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 1.0, 0.0);

			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, -1.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, 1.0);
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

Vector3D utility::getRandomPointOnSphere(float radius) {
	float theta = getRandomFloatBetween(0, 360);
	float phi = getRandomFloatBetween(-90, 90);

	float x = radius * cos(phi) * cos(theta);
	float y = radius * cos(phi) * sin(theta);
	float z = radius * sin(phi);

	return Vector3D(x, y, z);
}