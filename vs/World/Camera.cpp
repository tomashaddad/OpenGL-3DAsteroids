#define _USE_MATH_DEFINES
#include <cmath>

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

#include "Camera.h"
#include "Constants/CameraConstants.h"

#include "GlutHeaders.h"

Quaternion Camera::rotation = Quaternion::identity();

Camera::Camera() :
	look_at(Look::AHEAD),
	z_offset(-50),
	fov(CAMERA_FOV),
	znear(CAMERA_ZNEAR),
	zfar(CAMERA_ZFAR),
	aspect(0) {}

void Camera::lerpPositionTo(Vector3D new_position) {
	position = Vector3D::lerp(position, new_position, CAMERA_LERP_T);
}

void Camera::lerpRotationTo(Quaternion new_rotation) {
	rotation = Quaternion::slerp(rotation, new_rotation, CAMERA_LERP_T);
}

void Camera::look(const Look& look) { look_at = look; }

Vector3D Camera::getPosition() const { return position; }
const Quaternion& Camera::getRotation() { return rotation; }
const float& Camera::distanceFromShip() const { return z_offset; }
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