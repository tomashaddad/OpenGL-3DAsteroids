#ifndef I3D_MOUSE_H
#define I3D_MOUSE_H

class Mouse {
public:
	Mouse();

	void setMouseCoords(float x, float y);

	bool isHoldingLeftClick() const;
	void setHoldingLeftClick(bool state);

	bool isHoldingRightClick() const;
	void setHoldingRightClick(bool state);

	unsigned int X;
	unsigned int Y;

private:
	bool left_clicking_;
	bool right_clicking_;
};

#endif // I3D_MOUSE_H