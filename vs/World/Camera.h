#ifndef I3D_CAMERA_H
#define I3D_CAMERA_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

class Camera {
public:
	Camera(float fov, float znear, float zfar);

	Vector3D getPosition() const;
	Quaternion getRotation() const;

	const float& getFov() const;
	const float& getZNear() const;
	const float& getZFar() const;

	const float& getAspect() const;
	void setAspect(const float& aspect);

private:
	//Quaternion rotation;
	Vector3D position;

	float fov;
	float znear;
	float zfar;
	float aspect;
};

#endif // I3D_CAMERA_H