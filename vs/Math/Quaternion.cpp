#define _USE_MATH_DEFINES
#include <cmath>

#include "Quaternion.h"
#include "Utility.h"

// While I sort of understand some of this code I basically picked the stuff I needed from
// https://github.com/YclepticStudios/gmath/blob/master/src/Quaternion.hpp

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

Quaternion Quaternion::identity() { return Quaternion(); }

float Quaternion::dot(Quaternion lhs, Quaternion rhs) {
	return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z + lhs.W * rhs.W;
}

Quaternion Quaternion::inverse(const Quaternion& q) {
	float mag = magnitude(q);
	return conjugate(q) / (mag * mag);
}

float Quaternion::magnitude(const Quaternion &q) {
	return sqrtf(q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W);
}

Quaternion Quaternion::normalise(const Quaternion &q) {
	float mag = magnitude(q);

	return Quaternion(q.X / mag, q.Y / mag, q.Z / mag, q.W / mag);
}

// from https://stackoverflow.com/questions/31600717/how-to-generate-a-random-quaternion-quickly/44031492
Quaternion Quaternion::random() {
	float x, y, z, u, v, w, s;
	do { x = utility::randFloat(-1, 1); y = utility::randFloat(-1, 1); z = x * x + y * y; } while (z > 1);
	do { u = utility::randFloat(-1, 1); v = utility::randFloat(-1, 1); w = u * u + v * v; } while (w > 1);
	s = sqrt((1 - z) / w);
	return Quaternion(x, y, s * u, s * v);
}

std::array<float, 16> Quaternion::toMatrix(const Quaternion& q) {
	float X = q.X;
	float Y = q.Y;
	float Z = q.Z;
	float W = q.W;

	return {
		1 - 2 * (Z * Z + Y * Y),	2 * (X * Y + W * Z),		2 * (Z * X - W * Y),		0,
		2 * (X * Y - W * Z),		1 - 2 * (X * X + Z * Z),	2 * (Y * Z + W * X),		0,
		2 * (Z * X + W * Y),		2 * (Y * Z - W * X),		1 - 2 * (X * X + Y * Y),	0,
		0,							0,							0,							1
	};
}

Quaternion Quaternion::slerp(Quaternion a, Quaternion b, double t)
{
	if (t < 0) return normalise(a);
	else if (t > 1) return normalise(b);
	return slerpUnclamped(a, b, t);
}

Quaternion Quaternion::slerpUnclamped(Quaternion a, Quaternion b, double t)
{
	double n1;
	double n2;
	double n3 = dot(a, b);
	bool flag = false;
	if (n3 < 0)
	{
		flag = true;
		n3 = -n3;
	}
	if (n3 > 0.999999)
	{
		n2 = 1 - t;
		n1 = flag ? -t : t;
	}
	else
	{
		double n4 = acos(n3);
		double n5 = 1 / sin(n4);
		n2 = sin((1 - t) * n4) * n5;
		n1 = flag ? -sin(t * n4) * n5 : sin(t * n4) * n5;
	}
	Quaternion quaternion;
	quaternion.X = (n2 * a.X) + (n1 * b.X);
	quaternion.Y = (n2 * a.Y) + (n1 * b.Y);
	quaternion.Z = (n2 * a.Z) + (n1 * b.Z);
	quaternion.W = (n2 * a.W) + (n1 * b.W);
	return normalise(quaternion);
}

Quaternion Quaternion::conjugate(const Quaternion& q) {
	return Quaternion(-q.X, -q.Y, -q.Z, q.W);
}

Quaternion operator*(Quaternion lhs, Quaternion rhs) {
	return lhs *= rhs;
}

Quaternion& Quaternion::operator/=(const float rhs) {
	X /= rhs;
	Y /= rhs;
	Z /= rhs;
	W /= rhs;
	return *this;
}

Quaternion operator/(Quaternion lhs, const float rhs)
{
	return lhs /= rhs;
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
// See: https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
Vector3D operator*(Quaternion lhs, Vector3D rhs) {
	Vector3D v{ lhs.getX(), lhs.getY(), lhs.getZ() };
	float w = lhs.getW();

	float dot = Vector3D::dot(v, rhs);
	Vector3D cross = Vector3D::cross(v, rhs);

	return 2.0f * dot * v
		+ (w * w - Vector3D::dot(v, v)) * rhs
		+ 2.0f * w * cross;
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
