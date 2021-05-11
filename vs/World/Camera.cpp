#define _USE_MATH_DEFINES
#include <cmath>

#include "Camera.h"

Camera::Camera(float fov, float znear, float zfar) :
	fov(fov), znear(znear), zfar(zfar), aspect(0) {}

void Camera::lerpPositionTo(Vector3D new_position, float t) {
	previous_position = current_position;
	current_position = Vector3D::lerp(previous_position, new_position, t);
}

void Camera::lerpUpTo(Vector3D new_up, float t) {
	previous_up = current_up;
	current_up = Vector3D::lerp(previous_up, new_up, t);
}

Vector3D Camera::getPosition() const { return current_position; }
Vector3D Camera::getUp() const { return current_up; }

const float& Camera::getFov() const { return fov; }
const float& Camera::getZNear() const { return znear; }
const float& Camera::getZFar() const { return zfar; }

const float& Camera::getAspect() const { return aspect; };
void Camera::setAspect(const float& aspect) { this->aspect = aspect; }