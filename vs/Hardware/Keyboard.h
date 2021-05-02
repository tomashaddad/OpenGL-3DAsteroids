#ifndef I3D_KEYBOARD_H
#define I3D_KEYBOARD_H

#include <array>

class Keyboard {
public:
	Keyboard();
	void setPressed(unsigned char key, bool state);
	bool isPressed(unsigned char key);
	bool isAnyKeyPressed();
private:
	std::array<bool, 256> state_of;
};

#endif  // I3D_KEYBOARD_H