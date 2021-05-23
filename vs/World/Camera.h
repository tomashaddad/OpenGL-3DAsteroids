#ifndef I3D_CAMERA_H
#define I3D_CAMERA_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

class Camera {
public:
	Camera(float fov, float znear, float zfar);

	void lerpPositionTo(Vector3D new_position, float t);
	void lerpRotationTo(Quaternion new_rotation, float t);

	Vector3D getPosition() const;
	const float& getFov() const;
	const float& getZNear() const;
	const float& getZFar() const;

	const float& getAspect() const;
	void setAspect(const float& aspect);

	void translate();
	void rotate();

private:
	Quaternion rotation;
	Vector3D position;

	float fov;
	float znear;
	float zfar;
	float aspect;
};

#endif // I3D_CAMERA_H