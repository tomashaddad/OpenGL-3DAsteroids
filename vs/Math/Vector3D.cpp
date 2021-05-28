#define _USING_MATH_DEFINES
#include <cmath>
#include "Vector3D.h"
#include "Utility.h"

Vector3D::Vector3D() : X(0), Y(0), Z(0) {}
Vector3D::Vector3D(float x, float y, float z) : X(x), Y(y), Z(z) {}

Vector3D Vector3D::up() { return Vector3D(0, 1, 0); }
Vector3D Vector3D::right() { return Vector3D(1, 0, 0); }
Vector3D Vector3D::forward() { return Vector3D(0, 0, -1); }

float Vector3D::components_squared(Vector3D v) {
	return (v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z);
}

Vector3D Vector3D::cross(const Vector3D& lhs, const Vector3D& rhs) {
	return Vector3D{
		lhs.Y * rhs.Z - lhs.Z * rhs.Y,
		lhs.Z * rhs.X - lhs.X * rhs.Z,
		lhs.X * rhs.Y - lhs.Y * rhs.X
	};
}

float Vector3D::distance(const Vector3D& lhs, const Vector3D& rhs) {
	return Vector3D::magnitude(lhs - rhs);
}

// Returns the dot product of two 3D vectors
float Vector3D::dot(const Vector3D &lhs, const Vector3D &rhs) {
	return (lhs.X * rhs.X) + (lhs.Y * rhs.Y) + (lhs.Z * rhs.Z);
}

// angles given in degrees
Vector3D Vector3D::fromAngles(float theta, float phi, float magnitude) {
	float pi = acos(-1);
	theta *= pi / 180.0f;
	phi *= pi / 180.0f;

	float x = magnitude * cos(phi) * cos(theta);
	float y = magnitude * cos(phi) * sin(theta);
	float z = magnitude * sin(phi);

	return Vector3D(x, y, z);
}

Vector3D Vector3D::lerp(const Vector3D& a, const Vector3D& b, const float t) {
	return (b - a) * t + a;
}

float Vector3D::magnitude(Vector3D v) {
	return sqrt(components_squared(v));
}

Vector3D Vector3D::randomUnit() {
	float theta = utility::randFloat(0, 360);
	float phi = utility::randFloat(-180, 180);
	return fromAngles(theta, phi, 1);
}

Vector3D Vector3D::normalise(Vector3D v) {
	return v / magnitude(v);
}

Vector3D Vector3D::slerp(const Vector3D& a, const Vector3D& b, const float t) {
	float theta = acos(Vector3D::dot(Vector3D::normalise(a), Vector3D::normalise(b)));
	return (sin((1.0f - t) * theta) * a + sin(t * theta) * b) / sin(theta);
}

Vector3D Vector3D::red() {
	return Vector3D(1.0, 0.0, 0.0);
}

Vector3D Vector3D::green() {
	return Vector3D(0.0, 1.0, 0.0);
}

Vector3D Vector3D::blue() {
	return Vector3D(0.0, 0.0, 1.0);
}

Vector3D Vector3D::white() {
	return Vector3D(1.0, 1.0, 1.0);
}

std::array<float, 3> Vector3D::toArray(Vector3D v) {
	return { v.X, v.Y, v.Z };
}

// Helper function for colours with alpha values
std::array<float, 4> Vector3D::toArrayWithAlpha(Vector3D v, float a) {
	return { v.X, v.Y, v.Z, a};
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