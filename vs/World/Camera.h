#ifndef I3D_CAMERA_H
#define I3D_CAMERA_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"

#include "Enums/Enum.h"

class Camera {
public:
	Camera();

	void lerpPositionTo(Vector3D new_position);
	void lerpRotationTo(Quaternion new_rotation);

	void look(const Look& look);

	Vector3D getPosition() const;
	const static Quaternion& getRotation();
	const float& distanceFromShip() const;
	const float& getFov() const;
	const float& getZNear() const;
	const float& getZFar() const;

	const float& getAspect() const;
	void setAspect(const float& aspect);


	void translate();
	void rotate();
	Look look_at;

private:
	static Quaternion rotation;
	Vector3D position;

	float z_offset;

	float fov;
	float znear;
	float zfar;
	float aspect;
};

#endif // I3D_CAMERA_H