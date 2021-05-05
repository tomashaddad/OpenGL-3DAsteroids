#ifndef I3D_MOUSE_H
#define I3D_MOUSE_H

class Mouse {
public:
	Mouse();

	void setPosition(float x, float y);

	bool isHoldingLeftClick() const;
	void setHoldingLeftClick(bool state);

	bool isHoldingRightClick() const;
	void setHoldingRightClick(bool state);

	int X;
	int Y;

private:
	bool left_clicking;
	bool right_clicking;
};

#endif // I3D_MOUSE_H