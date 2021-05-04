#define _USE_MATH_DEFINES
#include <cmath>

#include "Quaternion.h"
#include "Utility.h"

Quaternion::Quaternion() : X(0), Y(0), Z(0), W(1) {}

Quaternion::Quaternion(Vector3D axis, float angle) {
	angle = Utility::toRadians(angle);
	float sine = sinf(angle * 0.5);

	X = axis.X * sine;
	Y = axis.Y * sine;
	Z = axis.Z * sine;
	W = cosf(angle * 0.5f);

	normalise();
}

Quaternion::Quaternion(float x, float y, float z, float w) :
	X(x), Y(y), Z(z), W(w) {}

float Quaternion::magnitude() const {
	return sqrtf(X * X + Y * Y + Z * Z + W * W);
}

void Quaternion::normalise() {
	float mag = magnitude();

	X /= mag;
	Y /= mag;
	Z /= mag;
	W /= mag;
}

std::array<float, 16> Quaternion::toMatrix() const {
	return {
		1 - 2*(Z*Z + Y*Y),	2*(X*Y - W*Z),		2*(Z*X + W*Y),		0,
		2*(X*Y + W*Z),		1 - 2*(X*X + Z*Z),	2*(Y*Z - W*X),		0,
		2*(Z*X - W*Y),		2*(Y*Z + W*X),		1 - 2*(X*X + Y*Y),	0,
		0,					0,					0,					X*X + Y*Y + Z*Z + W*W
	};
}

Quaternion Quaternion::conjugate() const {
	return Quaternion(-X, -Y, -Z, W);
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const {
	return Quaternion(
		W * rhs.getX() + X * rhs.getW() + Y * rhs.getZ() - Z * rhs.getY(),
		W * rhs.getY() - X * rhs.getZ() + Y * rhs.getW() + Z * rhs.getX(),
		W * rhs.getZ() + X * rhs.getY() - Y * rhs.getX() + Z * rhs.getW(),
		W * rhs.getW() - X * rhs.getX() - Y * rhs.getY() - Z * rhs.getZ()
	);
}

Vector3D Quaternion::operator*(const Vector3D& rhs) const {
	Quaternion pure = Quaternion(rhs.X, rhs.Y, rhs.Z, 0);
	Quaternion right = pure * conjugate();
	Quaternion left = *this * right;
	return Vector3D(left.X, left.Y, left.Z);
}

float Quaternion::getX() const { return X; }
float Quaternion::getY() const { return Y; }
float Quaternion::getZ() const { return Z; }
float Quaternion::getW() const { return W; }

std::ostream& operator<<(std::ostream& ostream, Quaternion& q)
{
	ostream << q.X << " " << q.Y << " "
			<< q.Z << " " << q.W << " " << std::endl;
	return ostream;
}
