#ifndef I3D_WALL_H
#define I3D_WALL_H

#include "Enums/Enum.h"

class Wall {
public:
	Wall(Side side);
	void draw() const;

	Side getSide() const;
	void setColour(const Colour colour);

private:
	Side side;
	Colour colour;
	float segments;
	float spacing;
};

#endif