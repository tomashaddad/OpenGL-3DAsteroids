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

	static Quaternion identity();

	static Quaternion conjugate(const Quaternion& q);
	static float dot(Quaternion lhs, Quaternion rhs);
	static Quaternion inverse(const Quaternion& q);
	static float magnitude(const Quaternion& q);
	static Quaternion normalise(const Quaternion& q);
	static Quaternion random();
	static Quaternion slerp(Quaternion a, Quaternion b, double t);
	static Quaternion slerpUnclamped(Quaternion a, Quaternion b, double t);
	static std::array<float, 16> toMatrix(const Quaternion& q);

	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;

	Quaternion& operator*=(const Quaternion& rhs);
	Quaternion& operator/=(const float rhs);

	friend std::ostream& operator<<(std::ostream& ostream, Quaternion& q);

private:
	float X;
	float Y;
	float Z;
	float W;
};

Quaternion operator*(Quaternion lhs, Quaternion rhs);
Quaternion operator/(Quaternion lhs, const float rhs);
Vector3D operator*(Quaternion lhs, Vector3D rhs);

#endif