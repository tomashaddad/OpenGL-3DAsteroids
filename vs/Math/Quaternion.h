#ifndef I3D_QUARTERNION_H
#define I3D_QUARTERNION_H

#include "Vector3D.h"
#include <array>
#include <iostream>

class Quaternion {
public:
	Quaternion();
	Quaternion(Vector3D axis, float angle);
	Quaternion(float x, float y, float z, float w);

	float magnitude() const;
	void normalise();
	std::array<float, 16> toMatrix() const;

	Quaternion conjugate() const;
	Quaternion operator*(const Quaternion& rhs) const;
	Vector3D operator*(const Vector3D& rhs) const;

	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;

	friend std::ostream& operator<<(std::ostream& ostream, Quaternion& q);

private:
	float X;
	float Y;
	float Z;
	float W;
};

#endif