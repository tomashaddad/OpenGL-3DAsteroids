#include "Vector3D.h"
#include <corecrt_math_defines.h>
#include <cmath>

Vector3D::Vector3D() : X(0), Y(0), Z(0) {}
Vector3D::Vector3D(float x, float y, float z) : X(x), Y(y), Z(z) {}

Vector3D Vector3D::up() { return Vector3D(0, 1, 0); }
Vector3D Vector3D::right() { return Vector3D(1, 0, 0); }
Vector3D Vector3D::backward() { return Vector3D(0, 0, -1); }

// Returns the dot product of two 3D vectors
float Vector3D::dot(Vector3D lhs, Vector3D rhs) {
	return (lhs.X * rhs.X) + (lhs.Y * rhs.Y) + (lhs.Z * rhs.Z);
}

// Returns a vector defined by angles alpha (in x, y) and beta (in z).
// A unit vector is returned if no magnitude is given
Vector3D Vector3D::from_angles(float alpha, float beta, float magnitude) {
	float xy = magnitude * cosf(beta);
	float x = xy * cosf(alpha);
	float y = xy * sinf(alpha);
	float z = magnitude * sinf(beta);
	return Vector3D(x, y, z);
}

float Vector3D::components_squared(Vector3D v) {
	return (v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z);
}

float Vector3D::magnitude(Vector3D v) {
	return sqrtf(components_squared(v));
}

Vector3D Vector3D::normalise(Vector3D v) {
	return v / magnitude(v);
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	return *this;
}

Vector3D& Vector3D::operator+=(const float rhs) {
	X += rhs;
	Y += rhs;
	Z += rhs;
	return *this;
}

Vector3D& Vector3D::operator-=(const float rhs) {
	X -= rhs;
	Y -= rhs;
	Z -= rhs;
	return *this;
}

Vector3D& Vector3D::operator*=(const float rhs) {
	X *= rhs;
	Y *= rhs;
	Z *= rhs;
	return *this;
}

Vector3D& Vector3D::operator/=(const float rhs) {
	X /= rhs;
	Y /= rhs;
	Z /= rhs;
	return *this;
}

std::ostream& operator<<(std::ostream& ostream, Vector3D& v) {
	ostream << v.X << " " << v.Y << " " << v.Z << std::endl;
	return ostream;
}

Vector3D operator-(const Vector3D& rhs) {
	return Vector3D(-rhs.X, -rhs.Y, -rhs.Z);
}

Vector3D operator+(Vector3D lhs, Vector3D rhs) {
	return lhs += rhs;
}

Vector3D operator-(Vector3D lhs, Vector3D rhs) {
	return lhs -= rhs;
}

Vector3D operator*(Vector3D lhs, const float rhs) {
	return lhs *= rhs;
}

Vector3D operator*(const float lhs, Vector3D rhs) {
	return rhs *= lhs;
}

Vector3D operator/(Vector3D lhs, const float rhs) {
	return lhs /= rhs;
}

Vector3D operator/(const float lhs, Vector3D rhs) {
	return rhs /= lhs;
}

bool operator==(const Vector3D& lhs, const Vector3D& rhs) {
	return lhs.X == rhs.X
		&& lhs.Y == rhs.Y
		&& lhs.Z == rhs.Z;
}

bool operator!=(const Vector3D& lhs, const Vector3D& rhs) {
	return !(lhs == rhs);
}