#ifndef I3D_MOUSE_H
#define I3D_MOUSE_H

#include <utility>

class Mouse {
public:
	Mouse();

	std::pair<unsigned int, unsigned int> getMouseCoords() const;
	void setMouseCoords(double x, double y);

	bool isHoldingLeftClick() const;
	void setHoldingLeftClick(bool state);

	bool isHoldingRightClick() const;
	void setHoldingRightClick(bool state);

private:
	unsigned int X;
	unsigned int Y;

	bool left_clicking_;
	bool right_clicking_;
};

#endif // I3D_MOUSE_H