#define _USE_MATH_DEFINES
#include <cmath>

#include "Camera.h"

Camera::Camera(float fov, float znear, float zfar) :
	fov(fov), znear(znear), zfar(zfar), aspect(0) {}

Vector3D Camera::getPosition() const { return position; }
//Quaternion Camera::getRotation() const { return rotation; }

const float& Camera::getFov() const { return fov; }
const float& Camera::getZNear() const { return znear; }
const float& Camera::getZFar() const { return zfar; }

const float& Camera::getAspect() const { return aspect; };
void Camera::setAspect(const float& aspect) { this->aspect = aspect; }