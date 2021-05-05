#define _USE_MATH_DEFINES
#include <cmath>

#include "Quaternion.h"
#include "Utility.h"

Quaternion::Quaternion() : X(0), Y(0), Z(0), W(1) {}

Quaternion::Quaternion(Vector3D axis, float angle) {
	float mag = Vector3D::magnitude(axis);
	angle = utility::toRadians(angle);
	float sine = sinf(angle * 0.5f);

	// Divide by magnitude for pure quaternion
	X = axis.X * sine / mag;
	Y = axis.Y * sine / mag;
	Z = axis.Z * sine / mag;
	W = cosf(angle * 0.5f);
}

Quaternion::Quaternion(float x, float y, float z, float w) :
	X(x), Y(y), Z(z), W(w) {}

float Quaternion::magnitude(const Quaternion &q) {
	return sqrtf(q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W);
}

Quaternion Quaternion::normalise(const Quaternion &q) {
	float mag = magnitude(q);

	return Quaternion(q.X / mag, q.Y / mag, q.Z / mag, q.W / mag);
}

std::array<float, 16> Quaternion::toMatrix(const Quaternion& q) {
	float X = q.X;
	float Y = q.Y;
	float Z = q.Z;
	float W = q.W;

	return {
		1 - 2*(Z*Z + Y*Y),	2*(X*Y - W*Z),		2*(Z*X + W*Y),		0,
		2*(X*Y + W*Z),		1 - 2*(X*X + Z*Z),	2*(Y*Z - W*X),		0,
		2*(Z*X - W*Y),		2*(Y*Z + W*X),		1 - 2*(X*X + Y*Y),	0,
		0,					0,					0,					1
	};
}

Quaternion Quaternion::conjugate(const Quaternion& q) {
	return Quaternion(-q.X, -q.Y, -q.Z, q.W);
}

Quaternion operator*(Quaternion lhs, Quaternion rhs) {
	return lhs *= rhs;
}

Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
	float rhsX = rhs.getX(), rhsY = rhs.getY(),
		rhsZ = rhs.getZ(), rhsW = rhs.getW();

	Quaternion q;

	q.X = W * rhsX + X * rhsW + Y * rhsZ - Z * rhsY;
	q.Y = W * rhsY - X * rhsZ + Y * rhsW + Z * rhsX;
	q.Z = W * rhsZ + X * rhsY - Y * rhsX + Z * rhsW;
	q.W = W * rhsW - X * rhsX - Y * rhsY - Z * rhsZ;

	*this = q;

	return *this;
}

// Quaternion->Vector multiplication is not commutiative, must be Q*V
Vector3D operator*(Quaternion lhs, Vector3D rhs) {
	Quaternion pure = Quaternion(rhs.X, rhs.Y, rhs.Z, 0);
	Quaternion right = pure * Quaternion::conjugate(lhs); // v * q-1
	Quaternion left = lhs * right; // q * (v * q-1)
	return Vector3D(left.getX(), left.getY(), left.getZ());
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
