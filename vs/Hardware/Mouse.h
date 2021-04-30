#ifndef I3D_MOUSE_H
#define I3D_MOUSE_H

#include "Math/Vector.h"

class Mouse {
public:
	Mouse();

	Vector getMouseCoords() const;
	void setMouseCoords(double x, double y);

	bool isHoldingLeftClick() const;
	void setHoldingLeftClick(bool state);

	bool isHoldingRightClick() const;
	void setHoldingRightClick(bool state);

private:
	Vector mouse_coords_;
	bool left_clicking_;
	bool right_clicking_;
};

#endif // I3D_MOUSE_H