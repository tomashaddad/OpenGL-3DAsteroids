#define _USE_MATH_DEFINES
#include <cmath>

#include "Camera.h"

#include "GlutHeaders.h"

Camera::Camera(float fov, float znear, float zfar) :
	fov(fov), znear(znear), zfar(zfar), aspect(0) {}

void Camera::lerpPositionTo(Vector3D new_position, float t) {
	position = Vector3D::lerp(position, new_position, t);
}

void Camera::lerpRotationTo(Quaternion new_rotation, float t) {
	rotation = Quaternion::slerp(rotation, new_rotation, t);
}

Vector3D Camera::getPosition() const { return position; }

const float& Camera::getFov() const { return fov; }
const float& Camera::getZNear() const { return znear; }
const float& Camera::getZFar() const { return zfar; }

const float& Camera::getAspect() const { return aspect; };
void Camera::setAspect(const float& aspect) { this->aspect = aspect; }

void Camera::translate() {
	glTranslatef(-position.X, -position.Y, -position.Z);
}

// If we want to look up, then we rotate the world down, so we need the camera's
// inverse quaternion to use with glMultMatrixf
void Camera::rotate() {
	glMultMatrixf(Quaternion::toMatrix(Quaternion::inverse(rotation)).data());
}