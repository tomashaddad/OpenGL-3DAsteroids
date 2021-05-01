#include "Vector3D.h"
#include <corecrt_math_defines.h>
#include <cmath>

Vector3D::Vector3D() : X(0), Y(0), Z(0) {}
Vector3D::Vector3D(float x, float y, float z) : X(x), Y(y), Z(z) {}

// Returns the dot product of two 3D vectors
float Vector3D::dot(Vector3D lhs, Vector3D rhs) {
	return (lhs.X * rhs.X) + (lhs.Y * rhs.Y) + (lhs.Z * rhs.Z);
}

// Returns a vector defined by angles alpha (in x, y) and beta (in z).
// A unit vector is returned if no magnitude is given
Vector3D Vector3D::from_angles(float alpha, float beta, float magnitude) {
	float x = magnitude * cosf(alpha) * cosf(beta);
	float y = magnitude * sinf(alpha) * cosf(beta);
	float z = magnitude * sinf(beta);
	return Vector3D(x, y, z);
}

float Vector3D::components_squared(Vector3D v) {
	return (v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z);
}

float Vector3D::magnitude(Vector3D v) {
	return sqrtf(components_squared(v));
}