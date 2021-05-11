#ifndef I3D_CAMERA_H
#define I3D_CAMERA_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

class Camera {
public:
	Camera(float fov, float znear, float zfar);

	void lerpPositionTo(Vector3D new_position, float t);
	void lerpUpTo(Vector3D new_up, float t);

	Vector3D getPosition() const;
	Vector3D getUp() const;
	const float& getFov() const;
	const float& getZNear() const;
	const float& getZFar() const;

	const float& getAspect() const;
	void setAspect(const float& aspect);

private:
	Vector3D current_position;
	Vector3D previous_position;

	Vector3D current_up;
	Vector3D previous_up;

	float fov;
	float znear;
	float zfar;
	float aspect;
};

#endif // I3D_CAMERA_H