#ifndef I3D_VECTOR_H
#define I3D_VECTOR_H

class Vector3D {
public:
	float X;
	float Y;
	float Z;

	Vector3D();
	Vector3D(float x, float y, float z);

	// Returns the dot product of two 3D vectors
	static float dot(Vector3D lhs, Vector3D rhs);

	// Returns a vector defined by angles alpha (in x, y) and beta (in z).
	// A unit vector is returned if no magnitude is given
	static Vector3D from_angles(float alpha, float beta, float magnitude = 1);

	static float components_squared(Vector3D v);

	static float magnitude(Vector3D v);
};

#endif // I3D_STRUCTS_H