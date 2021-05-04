#ifndef I3D_VECTOR_H
#define I3D_VECTOR_H

#include <iostream>

class Vector3D {
public:
	float X;
	float Y;
	float Z;

	Vector3D();
	Vector3D(float x, float y, float z);

	static Vector3D up();
	static Vector3D right();
	static Vector3D backward();

	static float dot(Vector3D lhs, Vector3D rhs);

	static Vector3D from_angles(float alpha, float beta, float magnitude = 1);

	static float components_squared(Vector3D v);

	static float magnitude(Vector3D v);

	static Vector3D normalise(Vector3D v);

	Vector3D& operator+=(const Vector3D& rhs); // Add vector to this vector
	Vector3D& operator-=(const Vector3D& rhs); // Subtract vector from this vector

	Vector3D& operator+=(const float rhs); // Add to all components
	Vector3D& operator-=(const float rhs); // Subtract from all components
	Vector3D& operator*=(const float rhs); // Multiply all components
	Vector3D& operator/=(const float rhs); // Divide all components

	friend std::ostream& operator<<(std::ostream& ostream, Vector3D& v);
};

Vector3D operator-(const Vector3D& rhs); // unary negation

Vector3D operator+(Vector3D lhs, Vector3D rhs); // Add two vectors
Vector3D operator-(Vector3D lhs, Vector3D rhs); // Subtract two vectors

// Commutative multiplication by a scalar
Vector3D operator*(Vector3D lhs, const float rhs);
Vector3D operator*(const float lhs, Vector3D rhs);

// Commutative division by a scalar
Vector3D operator/(Vector3D lhs, const float rhs);
Vector3D operator/(const float lhs, Vector3D rhs);

// Equality
bool operator==(const Vector3D& lhs, const Vector3D& rhs);
bool operator!=(const Vector3D& lhs, const Vector3D& rhs);

#endif // I3D_STRUCTS_H