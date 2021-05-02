#define _USE_MATH_DEFINES
#include <cmath>

#include "Camera.h"

#include <iostream>

Camera::Camera(float theta, float phi, float r) :
	theta(theta),
	phi(phi),
	radius(r)
{
	computeCoordinates();
}

void Camera::changeZoomBy(float zoom) {
	radius += zoom;
	computeCoordinates();
}

void Camera::changePhiBy(float angle) {
	phi += angle;
	computeCoordinates();
}

void Camera::changeThetaBy(float angle) {
	theta += angle;
	computeCoordinates();
}

void Camera::computeCoordinates() {
	float conversion = M_PI / 180;

	float phi_rad = phi * conversion;
	float theta_rad = theta * conversion;

	const float XY = radius * cosf(phi_rad);
	X = XY * cosf(theta_rad);
	Y = XY * sinf(theta_rad);
	Z = radius * sinf(phi_rad);

	std::cout << X << " " << Y << " " << Z << std::endl;
}