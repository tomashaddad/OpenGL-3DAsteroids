#ifndef I3D_SATELLITE_H
#define I3D_SATELLITE_H

#include "Math/Vector3D.h"

#include <array>

class Satellite {
public:
	Satellite();
	void update(float dt);
	void draw() const;

private:
	Vector3D position;
	Vector3D rotation_axis;
	float angle;
	float speed;
};

#endif // I3D_SATELLITE_H