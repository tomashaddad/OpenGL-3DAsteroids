#ifndef I3D_WALL_H
#define I3D_WALL_H

#include "Enums/Enum.h"
#include "Math/Vector3D.h"

class Wall {
public:
	Wall(Side side);
	void draw() const;

	Side getSide() const;
	void setColour(const Vector3D& colour);
	void setColour(const Vector3D& from, const Vector3D& to);

private:
	Side side;
	Vector3D colour;
	float segments;
	float spacing;
};

#endif